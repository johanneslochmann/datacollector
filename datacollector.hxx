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
    QAction* managePrescriptionTypesAction() const { return m_managePrescriptionTypes; }
    QAction* manageSurveysAction() const { return m_manageSurveys; }
    QAction* manageOrganizationUnitsAction() const { return m_manageOrganizationUnits; }
    QAction* manageIcd10DiagnosisAction() const { return m_manageIcd10Diagnosis; }
    QAction* manageAgatePrescriptionsAction() const { return m_manageAgatePrescriptions; }
    QAction* manageIcd10DiagnosisInSurveryAction() const { return m_manageIcd10DiagnosisInSurvery; }
    QAction* manageAgateDataAction() const { return m_manageAgateData; }

    QSqlQuery prepareAndPerformQuery(const QString& sql);
    QSqlQuery prepareQuery(const QString& sql);
    void performQuery(QSqlQuery& qry);
    bool performQueryWithExpectedSize(QSqlQuery& qry, int expectedSize);

    QSqlDatabase database();

    void showDatabaseError(const DatabaseError& err, const QString& info = QObject::tr("Database Error"), QWidget* parent=nullptr);

signals:
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
    void managePrescriptionTypes();
    void manageSurveys();
    void manageOrganizationUnits();
    void manageIcd10Diagnosis();
    void manageAgatePrescriptions();
    void manageIcd10DiagnosisInSurvery();
    void manageAgateData();

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
    QAction* m_managePrescriptionTypes;
    QAction* m_manageSurveys;
    QAction* m_manageOrganizationUnits;
    QAction* m_manageIcd10Diagnosis;
    QAction* m_manageAgatePrescriptions;
    QAction* m_manageIcd10DiagnosisInSurvery;
    QAction* m_manageAgateData;
};
