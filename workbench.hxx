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
    void manageAgeClasses();
    void manageSmokingHabits();
    void manageCollateralEffects();
    void manageCountries();
    void manageWeaponTypes();
    void manageHousingTypes();
    void manageModusOperandi();
    void manageCrimeTypes();
    void manageInformationSourceTypes();
    void manageCrimeCasePartyRoles();
    void manageJobs();
    void manageCrimeMotives();
    void manageMentalDiseases();
    void manageConsultancyResults();
    void manageWeapons();
    void manageCities();
    void manageCrimeCases();
    void manageProcessingStates();

    void manageSurveyData();
    void manageAgateData();
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
    TableManagementWidget* m_collateralEffects;
    TableManagementWidget* m_countries;
    TableManagementWidget* m_weaponTypes;
    TableManagementWidget* m_housingTypes;
    TableManagementWidget* m_modusOperandi;
    TableManagementWidget* m_crimeTypes;
    TableManagementWidget* m_informationSourceTypes;
    TableManagementWidget* m_crimeCasePartyRoles;
    TableManagementWidget* m_crimeMotives;
    TableManagementWidget* m_jobs;
    TableManagementWidget* m_mentalDiseases;
    TableManagementWidget* m_consultancyResults;
    TableManagementWidget* m_weapons;
    TableManagementWidget* m_cities;
    TableManagementWidget* m_processingStates;

    QWidget* m_surveyData;
    QWidget* m_agateData;
    QWidget* m_coreStatics;
    QWidget* m_crimeCases;
};
