#include "surveyform.hxx"

#include <QSqlQueryModel>
#include <QComboBox>
#include <QDebug>
#include <QTableView>
#include <QMessageBox>
#include <QSqlError>
#include <QPushButton>

#include "datacollector.hxx"
#include "databaseerror.hxx"
#include "surveydialog.hxx"
#include "icd10diagnosisselectiondialog.hxx"
#include "drugselectiondialog.hxx"
#include "prescribeabledrugselectiondialog.hxx"
#include "surveygateway.hxx"
#include "plasmaticleveldialog.hxx"

#include "ui_surveyform.h"

SurveyForm::SurveyForm(QWidget *parent) :
    QWidget(parent),
    ui(std::unique_ptr<Ui::SurveyForm>(new Ui::SurveyForm))
{
    ui->setupUi(this);

    prepareQueries();
    setupModels();

    connect(DataCollector::get(), &DataCollector::databaseAboutToClose, this, &SurveyForm::onDatabaseAboutToClose);
    connect(DataCollector::get(), &DataCollector::databaseAvailable, this, &SurveyForm::onDatabaseAvailable);
    connect(DataCollector::get(), &DataCollector::databaseUnavailable, this, &SurveyForm::onDatabaseUnavailable);

    connect(ui->projects, &QComboBox::currentTextChanged, this, &SurveyForm::onCurrentProjectChanged);
    connect(ui->campaigns, &QComboBox::currentTextChanged, this, &SurveyForm::onCurrentCampaignChanged);
    connect(ui->surveys, &QTableView::activated, this, &SurveyForm::onCurrentSurveyChanged);

    connect(ui->reloadSurveysW, &QPushButton::clicked, this, &SurveyForm::reloadSurveys);
    connect(ui->createSurveyW, &QPushButton::clicked, this, &SurveyForm::createSurvey);
    connect(ui->reloadIcd10DiagnosisW, &QPushButton::clicked, this, &SurveyForm::reloadIcd10Diagnosis);
    connect(ui->addIcd10DiagnosisW, &QPushButton::clicked, this, &SurveyForm::addIcd10Diagnosis);
    connect(ui->removeIcd10DiagnosisW, &QPushButton::clicked, this, &SurveyForm::removeIcd10Diagnosis);
    connect(ui->reloadIpOnDemandDrugsW, &QPushButton::clicked, this, &SurveyForm::reloadOnDemandDrugs);
    connect(ui->addIpOnDemandDrug, &QPushButton::clicked, this, &SurveyForm::addOnDemandDrug);
    connect(ui->removeIpOnDemandDrug, &QPushButton::clicked, this, &SurveyForm::removeOnDemandDrug);
    connect(ui->reloadIpRegularDrugs, &QPushButton::clicked, this, &SurveyForm::reloadIpRegularDrugs);
    connect(ui->addIpRegularDrug, &QPushButton::clicked, this, &SurveyForm::addIpRegularDrug);
    connect(ui->removeIpRegularDrug, &QPushButton::clicked, this, &SurveyForm::removeIpRegularDrug);
    connect(ui->reloadPlasmaticLevels, &QPushButton::clicked, this, &SurveyForm::reloadPlasmaticLevels);
    connect(ui->addPlasmaticLevel, &QPushButton::clicked, this, &SurveyForm::addPlasmaticLevel);
    connect(ui->removePlasmaticLevel, &QPushButton::clicked, this, &SurveyForm::removePlasmaticLevel);

    connect(this, &SurveyForm::projectFilterChanged, this, &SurveyForm::onProjectFilterChanged);
    connect(this, &SurveyForm::campaignFilterChanged, this, &SurveyForm::onCampaignFilterChanged);
    connect(this, &SurveyForm::surveyFilterChanged, this, &SurveyForm::onSurveyFilterChanged);

    reload();
}

SurveyForm::~SurveyForm()
{
}

void SurveyForm::onDatabaseAboutToClose()
{
    m_projectsModel->setQuery(QSqlQuery());
    m_campaignsModel->setQuery(QSqlQuery());
    m_surveysModel->setQuery(QSqlQuery());
    m_icd10Model->setQuery(QSqlQuery());
    m_ipOnDemandModel->setQuery(QSqlQuery());
    m_ipReqularModel->setQuery(QSqlQuery());
    m_ipPlasmaticLevelModel->setQuery(QSqlQuery());
    m_agateModel->setQuery(QSqlQuery());

    m_projectsQry.clear();
    m_campaignsQry.clear();
    m_surveysQry.clear();
    m_getCampaignIdQry.clear();
    m_getProjectIdQry.clear();
    m_icd10Qry.clear();
    m_ipOnDemandQry.clear();
    m_ipReqularQry.clear();
    m_ipPlasmaticLevelQry.clear();
    m_agateQry.clear();
}

void SurveyForm::onDatabaseAvailable()
{
    prepareQueries();
    setupModels();

    setEnabled(true);
}

void SurveyForm::onDatabaseUnavailable()
{
    setEnabled(false);
}

void SurveyForm::onCurrentProjectChanged(const QString &name)
{
    emit projectFilterChanged(0);

    if (name.isEmpty()) {
        return;
    }

    m_getProjectIdQry.bindValue(":projectName", name);

    if (!DataCollector::get()->performQueryWithExpectedSize(m_getProjectIdQry, 1, false)) {
        showError(m_getProjectIdQry.lastError(), tr("Failed to load Project"));
        return;
    }

    m_getProjectIdQry.first();

    m_currentProjectId = m_getProjectIdQry.value(0).toInt();

    emit projectFilterChanged(m_currentProjectId);
}

void SurveyForm::onCurrentCampaignChanged(const QString &name)
{
    emit campaignFilterChanged(0);

    if (name.isEmpty()) {
        return;
    }

    m_getCampaignIdQry.bindValue(":project_id", m_currentProjectId);
    m_getCampaignIdQry.bindValue(":campaign_name", name);

    if (!DataCollector::get()->performQueryWithExpectedSize(m_getCampaignIdQry, 1, false)) {
        showError(m_getCampaignIdQry.lastError(),
                  tr("Failed to load campaign with name '%1' in project '%2'.").arg(name).arg(ui->projects->currentText()));
        return;
    }

    m_getCampaignIdQry.first();
    m_currentCampaignId = m_getCampaignIdQry.value(0).toInt();

    emit campaignFilterChanged(m_currentCampaignId);
}

void SurveyForm::onCurrentSurveyChanged(const QModelIndex &idx)
{
    emit surveyFilterChanged(0);

    auto idIdx = ui->surveys->model()->index(idx.row(), 4);

    m_currentSurveyId = ui->surveys->model()->data(idIdx).toInt();

    emit surveyFilterChanged(m_currentSurveyId);
}

void SurveyForm::onProjectFilterChanged(int projectId)
{
    if (projectId < 1) {
        ui->campaigns->setEnabled(false);
        return;

        emit campaignFilterChanged(0);
    }

    m_campaignsQry.bindValue(":project_id", projectId);
    DataCollector::get()->performQuery(m_campaignsQry, false);

    m_campaignsModel->setQuery(m_campaignsQry);

    ui->campaigns->setModel(m_campaignsModel);
    ui->campaigns->setEnabled(true);
}

void SurveyForm::onCampaignFilterChanged(int campaignId)
{
    if (campaignId < 1) {
        ui->surveys->setEnabled(false);
        ui->tab->setEnabled(false);

        return;
    }

    reloadSurveys();
}

void SurveyForm::onSurveyFilterChanged(int surveyId)
{
    if (surveyId < 1) {
        ui->icd10View->setEnabled(false);
        ui->onDemandView->setEnabled(false);
        ui->ipRegularView->setEnabled(false);
        ui->ipPlasmaticLevelsView->setEnabled(false);
        ui->agateView->setEnabled(false);
        return;
    }

    reloadIcd10Diagnosis();
    reloadOnDemandDrugs();
    reloadIpRegularDrugs();
    reloadPlasmaticLevels();

    m_agateQry.bindValue(":survey_id", surveyId);

    DataCollector::get()->performQuery(m_agateQry, false);

    m_agateModel->setQuery(m_agateQry);

    ui->agateView->setModel(m_agateModel);

    ui->tab->setEnabled(true);
    ui->icd10View->setEnabled(true);
    ui->onDemandView->setEnabled(true);
    ui->ipRegularView->setEnabled(true);
    ui->ipPlasmaticLevelsView->setEnabled(true);
    ui->agateView->setEnabled(true);
}

void SurveyForm::reload()
{
    DataCollector::get()->performQuery(m_projectsQry, false);
    m_projectsModel->setQuery(m_projectsQry);
    ui->projects->setModel(m_projectsModel);
}

void SurveyForm::reloadSurveys()
{
    m_surveysQry.bindValue(":campaign_id", m_currentCampaignId);
    DataCollector::get()->performQuery(m_surveysQry, false);
    m_surveysModel->setQuery(m_surveysQry);
    ui->surveys->setModel(m_surveysModel);

    ui->surveys->setEnabled(true);

    qDebug() << "reloaded surveys for campaign: " << m_currentCampaignId;
}

void SurveyForm::createSurvey()
{
    auto dlg = new SurveyDialog(this, m_currentProjectId, m_currentCampaignId);

    if (QDialog::Accepted == dlg->exec()) {
        reloadSurveys();
    }
}

void SurveyForm::reloadIcd10Diagnosis()
{
    m_icd10Qry.bindValue(":survey_id", m_currentSurveyId);

    DataCollector::get()->performQuery(m_icd10Qry, false);
    m_icd10Model->setQuery(m_icd10Qry);

    ui->icd10View->setModel(m_icd10Model);
    ui->icd10View->hideColumn(1);
}

void SurveyForm::addIcd10Diagnosis()
{
    auto dlg = new Icd10DiagnosisSelectionDialog(this);

    if (QDialog::Accepted != dlg->exec()) {
        return;
    }

    try {
        SurveyGateway().addIcd10DiagnosisToSurvey(dlg->currentId(), m_currentSurveyId);
        DataCollector::get()->commit();

        reloadIcd10Diagnosis();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to add ICD10 Diagnosis to current survey."), this);
        DataCollector::get()->rollback();
    }
}

void SurveyForm::removeIcd10Diagnosis()
{
    auto selectedIndexes = ui->icd10View->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        return;
    }

    auto idx = selectedIndexes.first();

    if (QMessageBox::question(this, tr("Remove ICD10 Diagnosis?"),
                              tr("Remove Diagnosis <b>%1</b>?").arg(ui->icd10View->model()->data(idx).toString()),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    auto idIdx = ui->icd10View->model()->index(idx.row(), 1);

    auto selectedId = ui->icd10View->model()->data(idIdx).toInt();

    try {
        SurveyGateway().removeIcd10DiagnosisFromSurvey(selectedId);
        DataCollector::get()->commit();

        reloadIcd10Diagnosis();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to remove ICD10 Diagnosis from current survey."), this);
        DataCollector::get()->rollback();
    }
}

void SurveyForm::reloadOnDemandDrugs()
{
    m_ipOnDemandQry.bindValue(":survey_id", m_currentSurveyId);

    DataCollector::get()->performQuery(m_ipOnDemandQry, false);
    m_ipOnDemandModel->setQuery(m_ipOnDemandQry);

    ui->onDemandView->setModel(m_ipOnDemandModel);
    ui->onDemandView->hideColumn(1);
}

void SurveyForm::addOnDemandDrug()
{
    auto dlg = new DrugSelectionDialog(this);

    if (QDialog::Accepted != dlg->exec()) {
        return;
    }

    try {
        SurveyGateway().addOnDemandDrugToSurvey(dlg->currentId(), m_currentSurveyId);
        DataCollector::get()->commit();

        reloadOnDemandDrugs();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to add On Demand Drug to current survey."), this);
        DataCollector::get()->rollback();
    }
}

void SurveyForm::removeOnDemandDrug()
{
    auto selectedIndexes = ui->onDemandView->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        return;
    }

    auto idx = selectedIndexes.first();

    if (QMessageBox::question(this, tr("Remove Drug?"),
                              tr("Remove Drug <b>%1</b>?").arg(ui->onDemandView->model()->data(idx).toString()),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    auto idIdx = ui->onDemandView->model()->index(idx.row(), 1);

    auto selectedId = ui->onDemandView->model()->data(idIdx).toInt();

    try {
        SurveyGateway().removeOnDemandDrugFromSurvey(selectedId);
        DataCollector::get()->commit();

        reloadOnDemandDrugs();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to remove On Demand Drug from current survey."), this);
        DataCollector::get()->rollback();
    }
}

void SurveyForm::reloadIpRegularDrugs()
{
    m_ipReqularQry.bindValue(":survey_id", m_currentSurveyId);

    DataCollector::get()->performQuery(m_ipReqularQry, false);
    m_ipReqularModel->setQuery(m_ipReqularQry);

    ui->ipRegularView->setModel(m_ipReqularModel);
    ui->ipRegularView->hideColumn(7);
}

void SurveyForm::addIpRegularDrug()
{
    auto dlg = new PrescribeableDrugSelectionDialog(this);

    if (QDialog::Accepted != dlg->exec()) {
        return;
    }

    try {
        SurveyGateway().addRegularDrugToSurvey(dlg->currentId(),
                                               dlg->morningDosage(),
                                               dlg->lunchDosage(),
                                               dlg->noonDosage(),
                                               dlg->nightDosage(),
                                               m_currentSurveyId);
        DataCollector::get()->commit();

        reloadIpRegularDrugs();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to add Regular Drug Prescription to current survey."), this);
        DataCollector::get()->rollback();
    }
}

void SurveyForm::removeIpRegularDrug()
{
    auto selectedIndexes = ui->ipRegularView->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        return;
    }

    auto idx = selectedIndexes.first();

    if (QMessageBox::question(this, tr("Remove Prescription?"),
                              tr("Remove Prescription <b>%1</b>?").arg(ui->onDemandView->model()->data(idx).toString()),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    auto idIdx = ui->ipRegularView->model()->index(idx.row(), 7);

    auto selectedId = ui->ipRegularView->model()->data(idIdx).toInt();

    try {
        SurveyGateway().removeRegularDrugFromSurvey(selectedId);
        DataCollector::get()->commit();

        reloadIpRegularDrugs();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to remove Drug from current survey."), this);
        DataCollector::get()->rollback();
    }
}

void SurveyForm::reloadPlasmaticLevels()
{
    m_ipPlasmaticLevelQry.bindValue(":survey_id", m_currentSurveyId);

    DataCollector::get()->performQuery(m_ipPlasmaticLevelQry, false);
    m_ipPlasmaticLevelModel->setQuery(m_ipPlasmaticLevelQry);

    ui->ipPlasmaticLevelsView->setModel(m_ipPlasmaticLevelModel);
    ui->ipPlasmaticLevelsView->hideColumn(4);
}

void SurveyForm::addPlasmaticLevel()
{
    auto dlg = new PlasmaticLevelDialog(this);

    if (QDialog::Accepted != dlg->exec()) {
        return;
    }

    try {
        SurveyGateway().addPlasmaticLevelToSurvey(dlg->currentId(), dlg->value(), dlg->unitName(), m_currentSurveyId);
        DataCollector::get()->commit();

        reloadPlasmaticLevels();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to add Regular Drug Prescription to current survey."), this);
        DataCollector::get()->rollback();
    }
}

void SurveyForm::removePlasmaticLevel()
{
    auto selectedIndexes = ui->ipPlasmaticLevelsView->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        return;
    }

    auto idx = selectedIndexes.first();

    auto idIdx = ui->ipPlasmaticLevelsView->model()->index(idx.row(), 4);

    auto selectedId = ui->ipPlasmaticLevelsView->model()->data(idIdx).toInt();

    if (QMessageBox::question(this, tr("Remove Plasmatic Level?"),
                              tr("Remove Plasmatic Level <b>%1</b>?")
                              .arg(ui->ipPlasmaticLevelsView->model()->data(idx).toString()),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    try {
        SurveyGateway().removePlasmaticLevelFromSurvey(selectedId);
        DataCollector::get()->commit();

        reloadPlasmaticLevels();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to remove Plasmatic Level from current survey."), this);
        DataCollector::get()->rollback();
    }
}

void SurveyForm::prepareQueries()
{
    try {
        m_projectsQry = DataCollector::get()->prepareQuery("select name from core.project order by name asc;");
        m_campaignsQry = DataCollector::get()->prepareQuery("select name from core.campaign where project_id = :project_id order by name asc;");
        m_surveysQry = DataCollector::get()->prepareQuery("select "
                                                          "prob.external_id::text || ' [' || coalesce(prob.surname, '') || ', ' || coalesce(prob.first_name, '') || ']' as proband "
                                                          ", surv.survey_date as survey_date "
                                                          ", org.name as organization "
                                                          ", surv.description as comment "
                                                          ", surv.id as id "
                                                          "from core.proband prob "
                                                          "join core.survey surv on prob.id = surv.proband_id "
                                                          "join core.organization_unit org on surv.organization_unit_id = org.id "
                                                          "where surv.campaign_id = :campaign_id "
                                                          "order by proband asc;");

        m_getCampaignIdQry = DataCollector::get()->prepareQuery("select id from core.campaign where project_id = :project_id and name = :campaign_name");
        m_getProjectIdQry = DataCollector::get()->prepareQuery("select id from core.project where name = :projectName;");
        m_icd10Qry = DataCollector::get()->prepareQuery("select "
                                                        "icd10.name as diagnosis, "
                                                        "nm.id as id "
                                                        "from core.icd10_diagnosis icd10 "
                                                        "join core.icd10_survey nm on icd10.id = nm.icd10_diagnosis_id "
                                                        "join core.survey s on nm.survey_id = s.id "
                                                        "where s.id = :survey_id "
                                                        "order by diagnosis asc;");
        m_ipOnDemandQry = DataCollector::get()->prepareQuery("select "
                                                             "d.name as drug "
                                                             "from core.drug d "
                                                             "join core.optional_prescription nm on d.id = nm.drug_id "
                                                             "join core.survey s on nm.survey_id = s.id "
                                                             "where s.id = :survey_id "
                                                             "order by drug asc;");

        m_ipReqularQry = DataCollector::get()->prepareQuery("select "
                                                            "pd.name as drug "
                                                            ", nm.morning_dosage "
                                                            ", nm.lunch_dosage "
                                                            ", nm.noon_dosage "
                                                            ", nm.night_dosage "
                                                            ", am.name as administration_method_name "
                                                            ", u.name as unit_name"
                                                            ", nm.id as id "
                                                            "from core.prescribeable_drug pd "
                                                            "join core.regular_prescription nm on pd.id = nm.prescribeable_drug_id "
                                                            "join core.survey s on nm.survey_id = s.id "
                                                            "join core.unit u on pd.dosage_unit_id = u.id "
                                                            "join core.administration_method am on pd.administration_method_id = am.id "
                                                            "where s.id = :survey_id "
                                                            "order by drug asc;");

        m_ipPlasmaticLevelQry = DataCollector::get()->prepareQuery("select "
                                                                   "m.name as molecule "
                                                                   ", nm.concentration_value as measurement_value "
                                                                   ", u.name as measurement_unit "
                                                                   ", nm.description as description "
                                                                   ", nm.id as id "
                                                                   "from core.molecule m "
                                                                   "join core.plasmatic_level nm on m.id = nm.molecule_id "
                                                                   "join core.survey s on nm.survey_id = s.id "
                                                                   "join core.unit u on nm.unit_id = u.id "
                                                                   "where s.id = :survey_id "
                                                                   "order by molecule asc");

        m_agateQry = DataCollector::get()->prepareQuery("select "
                                                        "pt.name as prescription_type, "
                                                        "pd.name as prescribeable_drug, "
                                                        "nm.morning_dosage as morning, "
                                                        "nm.lunch_dosage as lunch, "
                                                        "nm.evening_dosage as evening, "
                                                        "nm.night_dosage as night, "
                                                        "u.name as dosage_unit, "
                                                        "nm.last_depot_injection_date, "
                                                        "nm.depot_injection_interval_in_days, "
                                                        "nm.description "
                                                        "from core.prescribeable_drug pd "
                                                        "join core.agate_prescription nm on pd.id = nm.prescribeable_drug_id "
                                                        "join core.survey s on nm.survey_id = s.id "
                                                        "join core.prescription_type pt on nm.prescription_type_id = pt.id "
                                                        "join core.unit u on nm.dosage_unit_id = u.id "
                                                        "where s.id = :survey_id "
                                                        "order by prescription_type asc, prescribeable_drug asc;");

    } catch(DatabaseError e) {
        showError(e);
    }
}

void SurveyForm::setupModels()
{
    m_projectsModel = new QSqlQueryModel(this);
    m_campaignsModel = new QSqlQueryModel(this);
    m_surveysModel = new QSqlQueryModel(this);
    m_icd10Model = new QSqlQueryModel(this);
    m_ipOnDemandModel = new QSqlQueryModel(this);
    m_ipReqularModel = new QSqlQueryModel(this);
    m_ipPlasmaticLevelModel = new QSqlQueryModel(this);
    m_agateModel = new QSqlQueryModel(this);

    ui->projects->setModel(m_projectsModel);
    ui->campaigns->setModel(m_campaignsModel);
    ui->surveys->setModel(m_surveysModel);
    ui->icd10View->setModel(m_icd10Model);
    ui->onDemandView->setModel(m_ipOnDemandModel);
    ui->ipRegularView->setModel(m_ipReqularModel);
    ui->ipPlasmaticLevelsView->setModel(m_ipPlasmaticLevelModel);
    ui->agateView->setModel(m_agateModel);

    ui->surveys->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->surveys->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->icd10View->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->icd10View->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->onDemandView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->onDemandView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ipRegularView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ipRegularView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ipPlasmaticLevelsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ipPlasmaticLevelsView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void SurveyForm::showError(QSqlError err, const QString &msg)
{
    QMessageBox::critical(this, tr("Database Error"),
                          QString("<p><b>%1</b></p><p>%2</p>").arg(msg).arg(err.text()));
}

void SurveyForm::showError(DatabaseError err)
{
    showError(err.error(), tr("Database Error"));
}
