#include "workbench.hxx"

#include "datacollector.hxx"

#include "channelintopatientmanagementwidget.hxx"
#include "drugadministrationmethodmanagementwidget.hxx"
#include "moleculeclassmanagementwidget.hxx"
#include "moleculemanagementwidget.hxx"
#include "sexmanagementwidget.hxx"
#include "unitmanagementwidget.hxx"
#include "projectmanagementwidget.hxx"
#include "campaignmanagementwidget.hxx"
#include "probandmanagementwidget.hxx"
#include "drugmanagementwidget.hxx"
#include "prescribeabledrugmanagmentwidget.hxx"
#include "prescribeabledrugcompositionmanagementwidget.hxx"
#include "surveymanagementwidget.hxx"
#include "organizationunitmanagementwidget.hxx"
#include "icd10diagnosismanagementwidget.hxx"
#include "ageclassmanagementwidget.hxx"
#include "smokinghabitsmanagementwidget.hxx"
#include "collateraleffectmanagementwidget.hxx"

#include "surveyform.hxx"
#include "manualagatewidget.hxx"
#include "corestatisticsform.hxx"

Workbench::Workbench(QWidget *parent)
    : QStackedWidget(parent)
{
    auto app = DataCollector::get();

    m_channelIntoPatient = new ChannelIntoPatientManagementWidget(this);
    m_drugAdministrationMethod = new DrugAdministrationMethodManagementWidget(this);
    m_moleculeClass = new MoleculeClassManagementWidget(this);
    m_molecules = new MoleculeManagementWidget(this);
    m_sexes = new SexManagementWidget(this);
    m_units = new UnitManagementWidget(this);
    m_projects = new ProjectManagementWidget(this);
    m_campaigns = new CampaignManagementWidget(this);
    m_probands = new ProbandManagementWidget(this);
    m_drugs = new DrugManagementWidget(this);
    m_prescribeableDrugs = new PrescribeableDrugManagmentWidget(this);
    m_prescribeableDrugsComposition = new PrescribeableDrugCompositionManagementWidget(this);
    m_surveys = new SurveyManagementWidget(this);
    m_organizationUnits = new OrganizationUnitManagementWidget(this);
    m_icd10Diagnosis = new Icd10DiagnosisManagementWidget(this);
    m_surveyData = new SurveyForm(this);
    m_coreStatics = new CoreStatisticsForm(this);
    m_ageClasses = new AgeClassManagementWidget(this);
    m_smokingHabits = new SmokingHabitsManagementWidget(this);
    m_collateralEffects = new CollateralEffectManagementWidget(this);
    m_agateData = new ManualAgateWidget(this);

    addWidget(m_channelIntoPatient);
    addWidget(m_drugAdministrationMethod);
    addWidget(m_moleculeClass);
    addWidget(m_molecules);
    addWidget(m_sexes);
    addWidget(m_units);
    addWidget(m_projects);
    addWidget(m_campaigns);
    addWidget(m_probands);
    addWidget(m_drugs);
    addWidget(m_prescribeableDrugs);
    addWidget(m_prescribeableDrugsComposition);
    addWidget(m_surveys);
    addWidget(m_organizationUnits);
    addWidget(m_icd10Diagnosis);
    addWidget(m_ageClasses);
    addWidget(m_smokingHabits);
    addWidget(m_collateralEffects);

    addWidget(m_surveyData);
    addWidget(m_agateData);
    addWidget(m_coreStatics);

    connect(app, &DataCollector::manageChannelsIntoPatient, this, &Workbench::manageChannelsIntoPatient);
    connect(app, &DataCollector::manageDrugAdministrationMethods, this, &Workbench::manageDrugAdministrationMethods);
    connect(app, &DataCollector::manageMoleculeClasses, this, &Workbench::manageMoleculeClasses);
    connect(app, &DataCollector::manageMolecules, this, &Workbench::manageMolecules);
    connect(app, &DataCollector::manageSexes, this, &Workbench::manageSexes);
    connect(app, &DataCollector::manageUnits, this, &Workbench::manageUnits);
    connect(app, &DataCollector::manageProjects, this, &Workbench::manageProjects);
    connect(app, &DataCollector::manageCampaigns, this, &Workbench::manageCampaigns);
    connect(app, &DataCollector::manageProbands, this, &Workbench::manageProbands);
    connect(app, &DataCollector::manageDrugs, this, &Workbench::manageDrugs);
    connect(app, &DataCollector::managePrescribeableDrugs, this, &Workbench::managePrescribeableDrugs);
    connect(app, &DataCollector::managePrescribeableDrugsComposition, this, &Workbench::managePrescribeableDrugsComposition);
    connect(app, &DataCollector::manageSurveys, this, &Workbench::manageSurveys);
    connect(app, &DataCollector::manageOrganizationUnits, this, &Workbench::manageOrganizationUnits);
    connect(app, &DataCollector::manageIcd10Diagnosis, this, &Workbench::manageIcd10Diagnosis);
    connect(app, &DataCollector::manageAgeClasses, this, &Workbench::manageAgeClasses);
    connect(app, &DataCollector::manageSmokingHabits, this, &Workbench::manageSmokingHabits);
    connect(app, &DataCollector::manageCollateralEffects, this, &Workbench::manageCollateralEffects);
    connect(app, &DataCollector::manageAgateData, this, &Workbench::manageAgateData);

    connect(app, &DataCollector::manageSurveyData, this, &Workbench::manageSurveyData);
    connect(app, &DataCollector::showCoreStatistics, this, &Workbench::showCoreStatistics);

    setCurrentWidget(m_surveyData);
}

void Workbench::manageChannelsIntoPatient()
{
    setCurrentWidget(m_channelIntoPatient);
}

void Workbench::manageDrugAdministrationMethods()
{
    setCurrentWidget(m_drugAdministrationMethod);
}

void Workbench::manageMoleculeClasses()
{
    setCurrentWidget(m_moleculeClass);
}

void Workbench::manageMolecules() {
    setCurrentWidget(m_molecules);
}

void Workbench::manageSexes()
{
    setCurrentWidget(m_sexes);
}

void Workbench::manageUnits()
{
    setCurrentWidget(m_units);
}

void Workbench::manageProjects()
{
    setCurrentWidget(m_projects);
}

void Workbench::manageCampaigns()
{
    setCurrentWidget(m_campaigns);
}

void Workbench::manageProbands() {
    setCurrentWidget(m_probands);
}

void Workbench::manageDrugs()
{
    setCurrentWidget(m_drugs);
}

void Workbench::managePrescribeableDrugs()
{
    setCurrentWidget(m_prescribeableDrugs);
}

void Workbench::managePrescribeableDrugsComposition()
{
    setCurrentWidget(m_prescribeableDrugsComposition);
}

void Workbench::manageSurveys()
{
    setCurrentWidget(m_surveys);
}

void Workbench::manageOrganizationUnits()
{
    setCurrentWidget(m_organizationUnits);
}

void Workbench::manageIcd10Diagnosis()
{
    setCurrentWidget(m_icd10Diagnosis);
}

void Workbench::manageSurveyData() {
    setCurrentWidget(m_surveyData);
}

void Workbench::manageAgateData()
{
    setCurrentWidget(m_agateData);
}

void Workbench::manageAgeClasses()
{
    setCurrentWidget(m_ageClasses);
}

void Workbench::manageSmokingHabits()
{
    setCurrentWidget(m_smokingHabits);
}

void Workbench::manageCollateralEffects()
{
    setCurrentWidget(m_collateralEffects);
}

void Workbench::showCoreStatistics()
{
    setCurrentWidget(m_coreStatics);
}
