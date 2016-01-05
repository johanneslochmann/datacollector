#pragma once

#include <QApplication>

#include <QSqlQuery>

#include "databaseerror.hxx"

const QString databaseConnectionName { "dbconn" };

class QAction;

class DataCollector : public QApplication
{
    Q_OBJECT
public:
    static DataCollector* get();

    explicit DataCollector(int& argc, char** argv);
    virtual ~DataCollector();

    QAction* quitAction() const { return m_quit; }
    QAction* openDatabaseAction() const { return m_openDatabase; }
    QAction* closeDatabaseAction() const { return m_closeDatabase; }
    QAction* pingDatabaseAction() const { return m_pingDatabase; }
    QAction* aboutProgramAction() const { return m_aboutProgram; }
    QAction* aboutQtAction() const { return m_aboutQt; }
    QAction* manageChannelsIntoPatientAction() const { return m_manageChannelsIntoPatient; }
    QAction* manageDrugAdministrationMethodsAction() const { return m_manageDrugAdministrationMethods; }
    QAction* manageMoleculeClassesAction() const { return m_manageMoleculeClasses; }
    QAction* manageMoleculesAction() const { return m_manageMolecules; }
    QAction* manageSexesAction() const { return m_manageSexes; }
    QAction* manageUnitsAction() const { return m_manageUnits; }
    QAction* manageProjectsAction() const { return m_manageProjects; }
    QAction* manageCampaignsAction() const { return m_manageCampaigns; }
    QAction* manageProbandsAction() const { return m_manageProbands; }
    QAction* manageDrugsAction() const { return m_manageDrugs; }
    QAction* managePrescribeableDrugsAction() const { return m_managePrescribeableDrugs; }
    QAction* managePrescribeableDrugsCompositionAction() const { return m_managePrescribeableDrugsComposition; }
    QAction* manageSurveysAction() const { return m_manageSurveys; }
    QAction* manageOrganizationUnitsAction() const { return m_manageOrganizationUnits; }
    QAction* manageIcd10DiagnosisAction() const { return m_manageIcd10Diagnosis; }
    QAction* manageAgeClassesAction() const { return m_manageAgeClasses; }
    QAction* manageSmokingHabitsAction() const { return m_manageSmokingHabits; }
    QAction* manageCollateralEffectsAction() const { return m_manageCollateralEffects; }
    QAction* manageCountriesAction() const { return m_manageCountries; }
    QAction* manageWeaponTypesAction() const { return m_manageWeaponTypes; }
    QAction* manageHousingTypesAction() const { return m_manageHousingTypes; }
    QAction* manageModusOperandiAction() const { return m_manageModusOperandi; }
    QAction* manageCrimeTypesAction() const { return m_manageCrimeTypes; }
    QAction* manageInformationSourceTypesAction() const { return m_manageInformationSourceTypes; }
    QAction* manageCrimeCasePartyRolesAction() const { return m_manageCrimeCasePartyRoles; }
    QAction* manageJobsAction() const { return m_manageJobs; }
    QAction* manageCrimeMotivesAction() const { return m_manageCrimeMotives; }
    QAction* manageMentalDiseasesAction() const { return m_manageMentalDiseases; }
    QAction* manageConsultancyResultsAction() const { return m_manageConsultancyResults; }
    QAction* manageWeaponsAction() const { return m_manageWeapons; }
    QAction* manageCitiesAction() const { return m_manageCities; }
    QAction* manageCrimeCasesAction() const { return m_manageCrimeCases; }
    QAction* manageProcessingStatesAction() const { return m_manageProcessingStates; }

    QAction* manageSurveyDataAction() const { return m_manageSurveyData; }
    QAction* manageAgateDataAction() const { return m_manageAgateData; }

    QAction* showAllStatisticsAction() const { return m_showAllStatistics; }

    QSqlQuery prepareAndPerformQuery(const QString& sql, bool createTransaction);
    QSqlQuery prepareQuery(const QString& sql);
    void begin();
    void commit();
    void rollback();

    void performQuery(QSqlQuery& qry, bool createTransaction);
    bool performQueryWithExpectedSize(QSqlQuery& qry, int expectedSize, bool createTransaction);

    QSqlDatabase database();

    void showDatabaseError(const DatabaseError& err, const QString& info = QObject::tr("Database Error"), QWidget* parent=nullptr);

signals:
    void databaseAboutToClose();
    void databaseAvailable();
    void databaseUnavailable();

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
    void showAllStatistics();

public slots:
    void openDatabase();
    void closeDatabase();
    void pingDatabase();
    void aboutProgram();

private:
    void initActions();

    QAction* m_quit;
    QAction* m_openDatabase;
    QAction* m_closeDatabase;
    QAction* m_pingDatabase;
    QAction* m_aboutProgram;
    QAction* m_aboutQt;
    QAction* m_manageChannelsIntoPatient;
    QAction* m_manageDrugAdministrationMethods;
    QAction* m_manageMoleculeClasses;
    QAction* m_manageMolecules;
    QAction* m_manageSexes;
    QAction* m_manageUnits;
    QAction* m_manageProjects;
    QAction* m_manageCampaigns;
    QAction* m_manageProbands;
    QAction* m_manageDrugs;
    QAction* m_managePrescribeableDrugs;
    QAction* m_managePrescribeableDrugsComposition;
    QAction* m_manageSurveys;
    QAction* m_manageOrganizationUnits;
    QAction* m_manageIcd10Diagnosis;
    QAction* m_manageAgeClasses;
    QAction* m_manageSmokingHabits;
    QAction* m_manageCollateralEffects;
    QAction* m_manageCountries;
    QAction* m_manageWeaponTypes;
    QAction* m_manageHousingTypes;
    QAction* m_manageModusOperandi;
    QAction* m_manageCrimeTypes;
    QAction* m_manageInformationSourceTypes;
    QAction* m_manageCrimeCasePartyRoles;
    QAction* m_manageJobs;
    QAction* m_manageCrimeMotives;
    QAction* m_manageMentalDiseases;
    QAction* m_manageConsultancyResults;
    QAction* m_manageWeapons;
    QAction* m_manageCities;
    QAction* m_manageCrimeCases;
    QAction* m_manageProcessingStates;

    QAction* m_manageSurveyData;
    QAction* m_manageAgateData;
    QAction* m_showAllStatistics;
};
