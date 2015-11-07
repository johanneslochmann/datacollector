#pragma once

#include <QMdiArea>
#include <QStackedWidget>

class TableManagementWidget;

class Workbench : public QStackedWidget
{
    Q_OBJECT
public:
    explicit Workbench(QWidget *parent = 0);

signals:

public slots:
    void manageChannelsIntoPatient();
    void manageDrugAdministrationMethods();
    void manageMoleculeClasses();
    void manageMolecules();
    void manageSexes();
    void manageUnits();
    void manageProjects();
    void manageCampaigns();
    void manageProbands();
    void manageDrugs();
    void managePrescribeableDrugs();
    void managePrescribeableDrugsComposition();
    void manageSurveys();
    void manageOrganizationUnits();
    void manageIcd10Diagnosis();
    void manageSurveyData();
    void manageAgeClasses();
    void manageSmokingHabits();
    void showCoreStatistics();

private:
    TableManagementWidget* m_channelIntoPatient;
    TableManagementWidget* m_drugAdministrationMethod;
    TableManagementWidget* m_moleculeClass;
    TableManagementWidget* m_molecules;
    TableManagementWidget* m_sexes;
    TableManagementWidget* m_units;
    TableManagementWidget* m_projects;
    TableManagementWidget* m_campaigns;
    TableManagementWidget* m_probands;
    TableManagementWidget* m_drugs;
    TableManagementWidget* m_prescribeableDrugs;
    TableManagementWidget* m_prescribeableDrugsComposition;
    TableManagementWidget* m_surveys;
    TableManagementWidget* m_organizationUnits;
    TableManagementWidget* m_icd10Diagnosis;
    TableManagementWidget* m_ageClasses;
    TableManagementWidget* m_smokingHabits;

    QWidget* m_surveyData;
    QWidget* m_coreStatics;
};
