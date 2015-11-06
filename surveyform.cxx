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
#include "ondemanddrugdialog.hxx"
#include "regulardrugdialog.hxx"
#include "surveygateway.hxx"
#include "plasmaticleveldialog.hxx"
#include "depotdrugdialog.hxx"

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
    connect(ui->reloadIpRegularDrugs, &QPushButton::clicked, this, &SurveyForm::reloadRegularDrugs);
    connect(ui->addIpRegularDrug, &QPushButton::clicked, this, &SurveyForm::addRegularDrug);
    connect(ui->removeIpRegularDrug, &QPushButton::clicked, this, &SurveyForm::removeRegularDrug);
    connect(ui->reloadPlasmaticLevels, &QPushButton::clicked, this, &SurveyForm::reloadPlasmaticLevels);
    connect(ui->addPlasmaticLevel, &QPushButton::clicked, this, &SurveyForm::addPlasmaticLevel);
    connect(ui->removePlasmaticLevel, &QPushButton::clicked, this, &SurveyForm::removePlasmaticLevel);
    connect(ui->reloadDepotDrugs, &QPushButton::clicked, this, &SurveyForm::reloadDepotDrugs);
    connect(ui->addDepotDrug, &QPushButton::clicked, this, &SurveyForm::addDepotDrug);
    connect(ui->removeDepotDrug, &QPushButton::clicked, this, &SurveyForm::removeDepotDrug);

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
    m_onDemandDrugsModel->setQuery(QSqlQuery());
    m_reqularDrugsModel->setQuery(QSqlQuery());
    m_plasmaticLevelsModel->setQuery(QSqlQuery());
    m_depotDrugsModel->setQuery(QSqlQuery());

    m_projectsQry.clear();
    m_campaignsQry.clear();
    m_surveysQry.clear();
    m_getCampaignIdQry.clear();
    m_getProjectIdQry.clear();
    m_icd10Qry.clear();
    m_onDemandDrugsQry.clear();
    m_reqularDrugsQry.clear();
    m_plasmaticLevelsQry.clear();
    m_depotDrugsQry.clear();
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
        ui->onDemandDrugsView->setEnabled(false);
        ui->regularDrugsView->setEnabled(false);
        ui->plasmaticLevelsView->setEnabled(false);
        ui->depotDrugsView->setEnabled(false);
        return;
    }

    reloadIcd10Diagnosis();
    reloadOnDemandDrugs();
    reloadRegularDrugs();
    reloadPlasmaticLevels();
    reloadDepotDrugs();

    ui->tab->setEnabled(true);
    ui->icd10View->setEnabled(true);
    ui->onDemandDrugsView->setEnabled(true);
    ui->regularDrugsView->setEnabled(true);
    ui->plasmaticLevelsView->setEnabled(true);
    ui->depotDrugsView->setEnabled(true);
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
    ui->icd10View->hideColumn(2);
}

void SurveyForm::addIcd10Diagnosis()
{
    auto dlg = new Icd10DiagnosisSelectionDialog(this);

    if (QDialog::Accepted != dlg->exec()) {
        return;
    }

    try {
        SurveyGateway().addIcd10DiagnosisToSurvey(dlg->currentId(), dlg->comment(), m_currentSurveyId);
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
    m_onDemandDrugsQry.bindValue(":survey_id", m_currentSurveyId);

    DataCollector::get()->performQuery(m_onDemandDrugsQry, false);
    m_onDemandDrugsModel->setQuery(m_onDemandDrugsQry);

    ui->onDemandDrugsView->setModel(m_onDemandDrugsModel);
    ui->onDemandDrugsView->hideColumn(2);
}

void SurveyForm::addOnDemandDrug()
{
    auto dlg = new OnDemandDrugDialog(this);

    if (QDialog::Accepted != dlg->exec()) {
        return;
    }

    try {
        SurveyGateway().addOnDemandDrugToSurvey(dlg->currentId(), dlg->comment(), m_currentSurveyId);
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
    auto selectedIndexes = ui->onDemandDrugsView->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        return;
    }

    auto idx = selectedIndexes.first();

    if (QMessageBox::question(this, tr("Remove Drug?"),
                              tr("Remove Drug <b>%1</b>?").arg(ui->onDemandDrugsView->model()->data(idx).toString()),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    auto idIdx = ui->onDemandDrugsView->model()->index(idx.row(), 1);

    auto selectedId = ui->onDemandDrugsView->model()->data(idIdx).toInt();

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

void SurveyForm::reloadRegularDrugs()
{
    m_reqularDrugsQry.bindValue(":survey_id", m_currentSurveyId);

    DataCollector::get()->performQuery(m_reqularDrugsQry, false);
    m_reqularDrugsModel->setQuery(m_reqularDrugsQry);

    ui->regularDrugsView->setModel(m_reqularDrugsModel);
    ui->regularDrugsView->hideColumn(7);
}

void SurveyForm::addRegularDrug()
{
    auto dlg = new RegularDrugDialog(this);

    if (QDialog::Accepted != dlg->exec()) {
        return;
    }

    try {
        SurveyGateway().addRegularDrugToSurvey(dlg->currentId(),
                                               dlg->morningDosage(),
                                               dlg->lunchDosage(),
                                               dlg->noonDosage(),
                                               dlg->nightDosage(),
                                               dlg->comment(),
                                               m_currentSurveyId);
        DataCollector::get()->commit();

        reloadRegularDrugs();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to add Regular Drug Prescription to current survey."), this);
        DataCollector::get()->rollback();
    }
}

void SurveyForm::removeRegularDrug()
{
    auto selectedIndexes = ui->regularDrugsView->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        return;
    }

    auto idx = selectedIndexes.first();

    if (QMessageBox::question(this, tr("Remove Prescription?"),
                              tr("Remove Prescription <b>%1</b>?").arg(ui->onDemandDrugsView->model()->data(idx).toString()),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    auto idIdx = ui->regularDrugsView->model()->index(idx.row(), 7);

    auto selectedId = ui->regularDrugsView->model()->data(idIdx).toInt();

    try {
        SurveyGateway().removeRegularDrugFromSurvey(selectedId);
        DataCollector::get()->commit();

        reloadRegularDrugs();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to remove Drug from current survey."), this);
        DataCollector::get()->rollback();
    }
}

void SurveyForm::reloadPlasmaticLevels()
{
    m_plasmaticLevelsQry.bindValue(":survey_id", m_currentSurveyId);

    DataCollector::get()->performQuery(m_plasmaticLevelsQry, false);
    m_plasmaticLevelsModel->setQuery(m_plasmaticLevelsQry);

    ui->plasmaticLevelsView->setModel(m_plasmaticLevelsModel);
    ui->plasmaticLevelsView->hideColumn(4);
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
    auto selectedIndexes = ui->plasmaticLevelsView->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        return;
    }

    auto idx = selectedIndexes.first();

    auto idIdx = ui->plasmaticLevelsView->model()->index(idx.row(), 4);

    auto selectedId = ui->plasmaticLevelsView->model()->data(idIdx).toInt();

    if (QMessageBox::question(this, tr("Remove Plasmatic Level?"),
                              tr("Remove Plasmatic Level <b>%1</b>?")
                              .arg(ui->plasmaticLevelsView->model()->data(idx).toString()),
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

void SurveyForm::reloadDepotDrugs()
{
    m_depotDrugsQry.bindValue(":survey_id", m_currentSurveyId);

    DataCollector::get()->performQuery(m_depotDrugsQry, false);
    m_depotDrugsModel->setQuery(m_depotDrugsQry);

    ui->depotDrugsView->setModel(m_depotDrugsModel);
    //ui->depotDrugsView->hideColumn(5);
}

void SurveyForm::addDepotDrug()
{
    auto dlg = new DepotDrugDialog(this);

    if (QDialog::Accepted != dlg->exec()) {
        return;
    }

    try {
        SurveyGateway().addDepotDrugToSurvey(dlg->currentId(),
                                             dlg->dosage(),
                                             dlg->lastInjectionDate(),
                                             dlg->interval(),
                                             m_currentSurveyId);
        DataCollector::get()->commit();

        reloadDepotDrugs();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to add Depot Drug Prescription to current survey."), this);
        DataCollector::get()->rollback();
    }
}

void SurveyForm::removeDepotDrug()
{
    auto selectedIndexes = ui->depotDrugsView->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        return;
    }

    auto idx = selectedIndexes.first();

    auto idIdx = ui->depotDrugsView->model()->index(idx.row(), 5);

    auto selectedId = ui->depotDrugsView->model()->data(idIdx).toInt();

    if (QMessageBox::question(this, tr("Remove Prescription?"),
                              tr("Remove Prescription <b>%1</b> (%2)?")
                              .arg(ui->depotDrugsView->model()->data(idx).toString())
                              .arg(selectedId),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    try {
        SurveyGateway().removeDepotDrugFromSurvey(selectedId);
        DataCollector::get()->commit();

        reloadDepotDrugs();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to remove Drug from current survey."), this);
        DataCollector::get()->rollback();
    }
}

void SurveyForm::prepareQueries()
{
    try {
        m_projectsQry = DataCollector::get()->prepareQuery("select name from core.project order by name asc;");
        m_campaignsQry = DataCollector::get()->prepareQuery("select name from core.campaign where project_id = :project_id order by name asc;");
        m_getCampaignIdQry = DataCollector::get()->prepareQuery("select id from core.campaign where project_id = :project_id and name = :campaign_name");
        m_getProjectIdQry = DataCollector::get()->prepareQuery("select id from core.project where name = :projectName;");

        m_surveysQry = DataCollector::get()->prepareQuery(QStringLiteral("select "
                                                                         "prob.external_id::text || ' [' || coalesce(prob.surname, '') || ', ' || coalesce(prob.first_name, '') || ']' as \"%1\" "
                                                                         ", surv.survey_date as \"%2\" "
                                                                         ", org.name as \"%3\" "
                                                                         ", surv.description as \"%4\" "
                                                                         ", surv.id as \"%5\" "
                                                                         "from core.proband prob "
                                                                         "join core.survey surv on prob.id = surv.proband_id "
                                                                         "join core.organization_unit org on surv.organization_unit_id = org.id "
                                                                         "where surv.campaign_id = :campaign_id "
                                                                         "order by 1, 2 asc;")
                                                          .arg(tr("Proband"))
                                                          .arg(tr("Survey Date"))
                                                          .arg(tr("Organization"))
                                                          .arg(tr("Description"))
                                                          .arg(tr("Survey ID")));

        m_icd10Qry = DataCollector::get()->prepareQuery(QStringLiteral("select "
                                                                       "icd10.name as \"%1\" "
                                                                       ", nm.description as \"%2\" "
                                                                       ", nm.id as id "
                                                                       "from core.icd10_diagnosis icd10 "
                                                                       "join core.icd10_survey nm on icd10.id = nm.icd10_diagnosis_id "
                                                                       "join core.survey s on nm.survey_id = s.id "
                                                                       "where s.id = :survey_id "
                                                                       "order by 1 asc;")
                                                        .arg(tr("ICD10 Diagnosis"))
                                                        .arg(tr("Description")));
        m_onDemandDrugsQry = DataCollector::get()->prepareQuery(QStringLiteral("select "
                                                                               "d.name as \"%1\" "
                                                                               ", nm.description as \"%2\" "
                                                                               "from core.drug d "
                                                                               "join core.optional_prescription nm on d.id = nm.drug_id "
                                                                               "join core.survey s on nm.survey_id = s.id "
                                                                               "where s.id = :survey_id "
                                                                               "order by 1 asc;")
                                                                .arg(tr("Drug"))
                                                                .arg(tr("Description")));

        m_reqularDrugsQry = DataCollector::get()->prepareQuery(QStringLiteral("select "
                                                                              "pd.name as \"%1\" "
                                                                              ", nm.morning_dosage as \"%2\" "
                                                                              ", nm.lunch_dosage as \"%3\" "
                                                                              ", nm.noon_dosage \"%4\" "
                                                                              ", nm.night_dosage \"%5\" "
                                                                              ", am.name as \"%6\" "
                                                                              ", u.name as \"%7\" "
                                                                              ", nm.id as \"%8\" "
                                                                              ", nm.description as \"%9\" "
                                                                              "from core.prescribeable_drug pd "
                                                                              "join core.regular_prescription nm on pd.id = nm.prescribeable_drug_id "
                                                                              "join core.survey s on nm.survey_id = s.id "
                                                                              "join core.unit u on pd.dosage_unit_id = u.id "
                                                                              "join core.administration_method am on pd.administration_method_id = am.id "
                                                                              "where s.id = :survey_id "
                                                                              "order by 1 asc;")
                                                               .arg(tr("Drug"))
                                                               .arg(tr("Morning"))
                                                               .arg(tr("Lunch"))
                                                               .arg(tr("Noon"))
                                                               .arg(tr("Night"))
                                                               .arg(tr("Administration Method"))
                                                               .arg(tr("Drug Dosage Unit"))
                                                               .arg(tr("Prescription ID"))
                                                               .arg(tr("Description")));

        m_plasmaticLevelsQry = DataCollector::get()->prepareQuery(QStringLiteral("select "
                                                                                 "m.name as \"%1\" "
                                                                                 ", nm.concentration_value as \"%2\" "
                                                                                 ", u.name as \"%3\" "
                                                                                 ", nm.description as \"%4\" "
                                                                                 ", nm.id as \"%5\" "
                                                                                 "from core.molecule m "
                                                                                 "join core.plasmatic_level nm on m.id = nm.molecule_id "
                                                                                 "join core.survey s on nm.survey_id = s.id "
                                                                                 "join core.unit u on nm.unit_id = u.id "
                                                                                 "where s.id = :survey_id "
                                                                                 "order by 1 asc")
                                                                  .arg(tr("Molecule"))
                                                                  .arg(tr("Measurement"))
                                                                  .arg(tr("Unit"))
                                                                  .arg(tr("Comment"))
                                                                  .arg(tr("Measurement ID")));

        m_depotDrugsQry = DataCollector::get()->prepareQuery(QStringLiteral("select "
                                                                            "pd.name as \"%1\", "
                                                                            "dp.last_injection_on as \"%2\", "
                                                                            "dp.dosage as \"%3\", "
                                                                            "dp.injection_interval_in_days as \"%4\", "
                                                                            "dp.description as \"%5\", "
                                                                            "dp.id as \"%6\" "
                                                                            "from core.survey s "
                                                                            "join core.depot_prescription dp on s.id = dp.survey_id "
                                                                            "join core.prescribeable_drug pd on dp.prescribeable_drug_id = pd.id "
                                                                            "where s.id = :survey_id "
                                                                            "order by 1 asc, 2 desc;")
                                                             .arg(tr("Prescribeable Drug"))
                                                             .arg(tr("Last Injection"))
                                                             .arg(tr("Dosage"))
                                                             .arg(tr("Interval [days]"))
                                                             .arg(tr("Comment"))
                                                             .arg(tr("Prescription ID")));
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
    m_onDemandDrugsModel = new QSqlQueryModel(this);
    m_reqularDrugsModel = new QSqlQueryModel(this);
    m_plasmaticLevelsModel = new QSqlQueryModel(this);
    m_depotDrugsModel = new QSqlQueryModel(this);

    ui->projects->setModel(m_projectsModel);
    ui->campaigns->setModel(m_campaignsModel);
    ui->surveys->setModel(m_surveysModel);
    ui->icd10View->setModel(m_icd10Model);
    ui->onDemandDrugsView->setModel(m_onDemandDrugsModel);
    ui->regularDrugsView->setModel(m_reqularDrugsModel);
    ui->plasmaticLevelsView->setModel(m_plasmaticLevelsModel);
    ui->depotDrugsView->setModel(m_depotDrugsModel);

    ui->surveys->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->surveys->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->surveys->setSortingEnabled(true);

    ui->icd10View->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->icd10View->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->icd10View->setSortingEnabled(true);

    ui->onDemandDrugsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->onDemandDrugsView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->onDemandDrugsView->setSortingEnabled(true);

    ui->regularDrugsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->regularDrugsView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->regularDrugsView->setSortingEnabled(true);

    ui->plasmaticLevelsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->plasmaticLevelsView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->plasmaticLevelsView->setSortingEnabled(true);

    ui->depotDrugsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->depotDrugsView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->depotDrugsView->setSortingEnabled(true);
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
