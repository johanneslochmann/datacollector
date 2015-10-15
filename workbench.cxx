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
