#include "workbench.hxx"

#include "datacollector.hxx"

#include "channelintopatientmanagementwidget.hxx"
#include "drugadministrationmethodmanagementwidget.hxx"
#include "moleculeclassmanagementwidget.hxx"
#include "moleculemanagementwidget.hxx"
#include "sexmanagementwidget.hxx"

Workbench::Workbench(QWidget *parent)
    : QStackedWidget(parent)
{
    auto app = DataCollector::get();

    m_channelIntoPatient = new ChannelIntoPatientManagementWidget(this);
    m_drugAdministrationMethod = new DrugAdministrationMethodManagementWidget(this);
    m_moleculeClass = new MoleculeClassManagementWidget(this);
    m_molecules = new MoleculeManagementWidget(this);
    m_sexes = new SexManagementWidget(this);

    addWidget(m_channelIntoPatient);
    addWidget(m_drugAdministrationMethod);
    addWidget(m_moleculeClass);
    addWidget(m_molecules);
    addWidget(m_sexes);

    connect(app, &DataCollector::manageChannelsIntoPatient, this, &Workbench::manageChannelsIntoPatient);
    connect(app, &DataCollector::manageDrugAdministrationMethods, this, &Workbench::manageDrugAdministrationMethods);
    connect(app, &DataCollector::manageMoleculeClasses, this, &Workbench::manageMoleculeClasses);
    connect(app, &DataCollector::manageMolecules, this, &Workbench::manageMolecules);
    connect(app, &DataCollector::manageSexes, this, &Workbench::manageSexes);
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
