#include "agateform.hxx"

#include <QSqlQueryModel>
#include <QComboBox>
#include <QDebug>
#include <QTableView>
#include <QMessageBox>
#include <QSqlError>
#include <QPushButton>

#include "ui_agateform.h"

#include "datacollector.hxx"
#include "databaseerror.hxx"
#include "surveydialog.hxx"

AgateForm::AgateForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AgateForm)
{
    ui->setupUi(this);

    prepareQueries();
    setupModels();

    connect(ui->projects, &QComboBox::currentTextChanged, this, &AgateForm::onCurrentProjectChanged);
    connect(ui->campaigns, &QComboBox::currentTextChanged, this, &AgateForm::onCurrentCampaignChanged);
    connect(ui->surveys, &QTableView::activated, this, &AgateForm::onCurrentSurveyChanged);

    connect(ui->reloadSurveysW, &QPushButton::clicked, this, &AgateForm::reloadSurveys);
    connect(ui->createSurveyW, &QPushButton::clicked, this, &AgateForm::createSurvey);

    connect(this, &AgateForm::projectFilterChanged, this, &AgateForm::onProjectFilterChanged);
    connect(this, &AgateForm::campaignFilterChanged, this, &AgateForm::onCampaignFilterChanged);
    connect(this, &AgateForm::surveyFilterChanged, this, &AgateForm::onSurveyFilterChanged);

    reload();
}

AgateForm::~AgateForm()
{
    delete ui;
}

void AgateForm::onCurrentProjectChanged(const QString &name)
{
    emit projectFilterChanged(0);

    if (name.isEmpty()) {
        return;
    }

    m_getProjectIdQry.bindValue(":projectName", name);

    if (!DataCollector::get()->performQueryWithExpectedSize(m_getProjectIdQry, 1)) {
        showError(m_getProjectIdQry.lastError(), tr("Failed to load Project"));
        return;
    }

    m_getProjectIdQry.first();

    m_currentProjectId = m_getProjectIdQry.value(0).toInt();

    emit projectFilterChanged(m_currentProjectId);
}

void AgateForm::onCurrentCampaignChanged(const QString &name)
{
    emit campaignFilterChanged(0);

    if (name.isEmpty()) {
        return;
    }

    m_getCampaignIdQry.bindValue(":project_id", m_currentProjectId);
    m_getCampaignIdQry.bindValue(":campaign_name", name);

    if (!DataCollector::get()->performQueryWithExpectedSize(m_getCampaignIdQry, 1)) {
        showError(m_getCampaignIdQry.lastError(),
                  tr("Failed to load campaign with name '%1' in project '%2'.").arg(name).arg(ui->projects->currentText()));
        return;
    }

    m_getCampaignIdQry.first();
    m_currentCampaignId = m_getCampaignIdQry.value(0).toInt();

    emit campaignFilterChanged(m_currentCampaignId);
}

void AgateForm::onCurrentSurveyChanged(const QModelIndex &idx)
{
    emit surveyFilterChanged(0);

    auto idIdx = ui->surveys->model()->index(idx.row(), 4);

    emit surveyFilterChanged(ui->surveys->model()->data(idIdx).toInt());
}

void AgateForm::onProjectFilterChanged(int projectId)
{
    if (projectId < 1) {
        ui->campaigns->setEnabled(false);
        return;

        emit campaignFilterChanged(0);
    }

    m_campaignsQry.bindValue(":project_id", projectId);
    DataCollector::get()->performQuery(m_campaignsQry);

    m_campaignsModel->setQuery(m_campaignsQry);

    ui->campaigns->setModel(m_campaignsModel);
    ui->campaigns->setEnabled(true);
}

void AgateForm::onCampaignFilterChanged(int campaignId)
{
    if (campaignId < 1) {
        ui->surveys->setEnabled(false);
        ui->tab->setEnabled(false);

        return;
    }

    reloadSurveys();
}

void AgateForm::onSurveyFilterChanged(int surveyId)
{
    if (surveyId < 1) {
        ui->icd10View->setEnabled(false);
        ui->ipOnDemandView->setEnabled(false);
        ui->ipRegularView->setEnabled(false);
        ui->ipPlasmaticLevelsView->setEnabled(false);
        ui->agateView->setEnabled(false);
        return;
    }

    m_icd10Qry.bindValue(":survey_id", surveyId);
    m_ipOnDemandQry.bindValue(":survey_id", surveyId);
    m_ipReqularQry.bindValue(":survey_id", surveyId);
    m_ipPlasmaticLevelQry.bindValue(":survey_id", surveyId);
    m_agateQry.bindValue(":survey_id", surveyId);

    DataCollector::get()->performQuery(m_icd10Qry);
    DataCollector::get()->performQuery(m_ipOnDemandQry);
    DataCollector::get()->performQuery(m_ipReqularQry);
    DataCollector::get()->performQuery(m_ipPlasmaticLevelQry);
    DataCollector::get()->performQuery(m_agateQry);

    m_icd10Model->setQuery(m_icd10Qry);
    m_ipOnDemandModel->setQuery(m_ipOnDemandQry);;
    m_ipReqularModel->setQuery(m_ipReqularQry);
    m_ipPlasmaticLevelModel->setQuery(m_ipPlasmaticLevelQry);
    m_agateModel->setQuery(m_agateQry);

    ui->icd10View->setModel(m_icd10Model);
    ui->ipOnDemandView->setModel(m_ipOnDemandModel);
    ui->ipRegularView->setModel(m_ipReqularModel);
    ui->ipPlasmaticLevelsView->setModel(m_ipPlasmaticLevelModel);
    ui->agateView->setModel(m_agateModel);

    ui->tab->setEnabled(true);
    ui->icd10View->setEnabled(true);
    ui->ipOnDemandView->setEnabled(true);
    ui->ipRegularView->setEnabled(true);
    ui->ipPlasmaticLevelsView->setEnabled(true);
    ui->agateView->setEnabled(true);
}

void AgateForm::reload()
{
    DataCollector::get()->performQuery(m_projectsQry);
    m_projectsModel->setQuery(m_projectsQry);
    ui->projects->setModel(m_projectsModel);
}

void AgateForm::reloadSurveys()
{
    m_surveysQry.bindValue(":campaign_id", m_currentCampaignId);
    DataCollector::get()->performQuery(m_surveysQry);
    m_surveysModel->setQuery(m_surveysQry);
    ui->surveys->setModel(m_surveysModel);

    ui->surveys->setEnabled(true);
}

void AgateForm::createSurvey()
{
    auto dlg = new SurveyDialog(this, m_currentProjectId, m_currentCampaignId);

    if (QDialog::Accepted == dlg->exec()) {
        reloadSurveys();
    }
}

void AgateForm::prepareQueries()
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
                                                          "join core.survey surv on prob.id = surv.id "
                                                          "join core.organization_unit org on surv.organization_unit_id = org.id "
                                                          "where surv.campaign_id = :campaign_id "
                                                          "order by proband asc;");

        m_getCampaignIdQry = DataCollector::get()->prepareQuery("select id from core.campaign where project_id = :project_id and name = :campaign_name");
        m_getProjectIdQry = DataCollector::get()->prepareQuery("select id from core.project where name = :projectName;");
        m_icd10Qry = DataCollector::get()->prepareQuery("select "
                                                        "icd10.name as diagnosis "
                                                        "from core.icd10_diagnosis icd10 "
                                                        "join core.icd10_survey nm on icd10.id = nm.icd10_diagnosis_id "
                                                        "join core.survey s on nm.survey_id = nm.survey_id "
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
                                                            "from core.prescribeable_drug pd "
                                                            "join core.regular_prescription nm on pd.id = nm.prescribeable_drug_id "
                                                            "join core.survey s on nm.survey_id = s.id "
                                                            "where s.id = :survey_id "
                                                            "order by drug asc");

        m_ipPlasmaticLevelQry = DataCollector::get()->prepareQuery("select "
                                                                   "m.name as molecule "
                                                                   ", nm.concentration_value as measurement_value "
                                                                   ", nm.description as description "
                                                                   "from core.molecule m "
                                                                   "join core.plasmatic_level nm on m.id = nm.molecule_id "
                                                                   "join core.survey s on nm.survey_id = s.id "
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

void AgateForm::setupModels()
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
    ui->ipOnDemandView->setModel(m_ipOnDemandModel);
    ui->ipRegularView->setModel(m_ipReqularModel);
    ui->ipPlasmaticLevelsView->setModel(m_ipPlasmaticLevelModel);
    ui->agateView->setModel(m_agateModel);

    ui->surveys->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->surveys->setSelectionMode(QAbstractItemView::SingleSelection);
}

void AgateForm::showError(QSqlError err, const QString &msg)
{
    QMessageBox::critical(this, tr("Database Error"),
                          QString("<p><b>%1</b></p><p>%2</p>").arg(msg).arg(err.text()));
}

void AgateForm::showError(DatabaseError err)
{
    showError(err.error(), tr("Database Error"));
}
