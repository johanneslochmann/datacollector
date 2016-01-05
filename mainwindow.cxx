#include "mainwindow.hxx"

#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTimer>

#include "datacollector.hxx"
#include "databaseconnectionstatuslabel.hxx"
#include "workbench.hxx"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initMenues();
    initStatusBar();

    auto app = DataCollector::get();

    connect(app, &DataCollector::databaseAboutToClose, this, &MainWindow::databaseAboutToClose);
    connect(app, &DataCollector::databaseAvailable, this, &MainWindow::databaseAvailable);
    connect(app, &DataCollector::databaseUnavailable, this, &MainWindow::databaseUnavailable);

    QTimer::singleShot(0, app->openDatabaseAction(), &QAction::trigger);
}

MainWindow::~MainWindow()
{
}

void MainWindow::databaseAboutToClose()
{
    delete m_wb;
}

void MainWindow::databaseAvailable()
{
    m_wb = new Workbench(this);
    setCentralWidget(m_wb);
    m_wb->showMaximized();
}

void MainWindow::databaseUnavailable()
{
}

void MainWindow::createFileMenu(DataCollector *app)
{
    m_fileM = new QMenu(tr("&File"), this);
    m_fileM->addAction(app->quitAction());
}

void MainWindow::createDatabaseMenu(DataCollector *app)
{
    m_databaseM = new QMenu(tr("&Database"), this);
    m_databaseM->addAction(app->openDatabaseAction());
    m_databaseM->addAction(app->closeDatabaseAction());
    m_databaseM->addSeparator();
    m_databaseM->addAction(app->pingDatabaseAction());
}

void MainWindow::createAdminMenu(DataCollector *app)
{
    m_adminM = new QMenu(tr("&Administration"), this);
    m_adminM->addAction(app->manageProbandsAction());
    m_adminM->addSeparator();
    m_adminM->addAction(app->manageProjectsAction());
    m_adminM->addAction(app->manageCampaignsAction());
    m_adminM->addAction(app->manageInformationSourceTypesAction());
    m_adminM->addAction(app->manageJobsAction());
    m_adminM->addAction(app->manageProcessingStatesAction());
    m_adminM->addSeparator();
    m_adminM->addAction(app->manageOrganizationUnitsAction());
    m_adminM->addAction(app->manageIcd10DiagnosisAction());
    m_adminM->addAction(app->manageCollateralEffectsAction());
    m_adminM->addSeparator();
    m_adminM->addAction(app->manageChannelsIntoPatientAction());
    m_adminM->addAction(app->manageDrugAdministrationMethodsAction());
    m_adminM->addAction(app->manageMoleculeClassesAction());
    m_adminM->addAction(app->manageMoleculesAction());
    m_adminM->addAction(app->manageDrugsAction());
    m_adminM->addAction(app->managePrescribeableDrugsAction());
    m_adminM->addAction(app->managePrescribeableDrugsCompositionAction());
    m_adminM->addSeparator();
    m_adminM->addAction(app->manageSexesAction());
    m_adminM->addAction(app->manageUnitsAction());
    m_adminM->addAction(app->manageAgeClassesAction());
    m_adminM->addAction(app->manageSmokingHabitsAction());
    m_adminM->addSeparator();
    m_adminM->addAction(app->manageCountriesAction());
    m_adminM->addAction(app->manageCitiesAction());
    m_adminM->addAction(app->manageHousingTypesAction());
    m_adminM->addSeparator();
    m_adminM->addAction(app->manageCrimeCasesAction());
    m_adminM->addAction(app->manageWeaponTypesAction());
    m_adminM->addAction(app->manageWeaponsAction());
    m_adminM->addAction(app->manageModusOperandiAction());
    m_adminM->addAction(app->manageCrimeTypesAction());
    m_adminM->addAction(app->manageCrimeCasePartyRolesAction());
    m_adminM->addAction(app->manageCrimeMotivesAction());
    m_adminM->addAction(app->manageMentalDiseasesAction());
    m_adminM->addAction(app->manageConsultancyResultsAction());
    m_adminM->addSeparator();
    m_adminM->addAction(app->manageSurveysAction());
    m_adminM->addSeparator();
    m_adminM->addAction(app->manageSurveyDataAction());
}

void MainWindow::createProjectMenu(DataCollector *app)
{
    m_projectM = new QMenu(tr("&Projects"), this);
    m_projectM->addAction(app->manageProjectsAction());
    m_projectM->addAction(app->manageCampaignsAction());
    m_projectM->addAction(app->manageProcessingStatesAction());
}

void MainWindow::createPharmacologyMenu(DataCollector *app)
{
    m_pharmacologyM = new QMenu(tr("Ph&armacology"), this);
    m_pharmacologyM->addAction(app->manageChannelsIntoPatientAction());
    m_pharmacologyM->addAction(app->manageDrugAdministrationMethodsAction());
    m_pharmacologyM->addAction(app->manageMoleculeClassesAction());
    m_pharmacologyM->addAction(app->manageMoleculesAction());
    m_pharmacologyM->addAction(app->manageDrugsAction());
    m_pharmacologyM->addAction(app->managePrescribeableDrugsAction());
    m_pharmacologyM->addAction(app->managePrescribeableDrugsCompositionAction());
    m_pharmacologyM->addAction(app->manageSmokingHabitsAction());
}

void MainWindow::createAgateMenu(DataCollector *app)
{
    m_agateM = new QMenu(tr("&AGATE"), this);
    m_agateM->addAction(app->manageAgateDataAction());
    m_agateM->addSeparator();
    m_agateM->addAction(app->manageProjectsAction());
    m_agateM->addAction(app->manageCampaignsAction());
    m_agateM->addSeparator();
    m_agateM->addAction(app->manageOrganizationUnitsAction());
    m_agateM->addAction(app->manageIcd10DiagnosisAction());
    m_agateM->addSeparator();
    m_agateM->addAction(app->manageChannelsIntoPatientAction());
    m_agateM->addAction(app->manageDrugAdministrationMethodsAction());
    m_agateM->addAction(app->manageMoleculeClassesAction());
    m_agateM->addAction(app->manageMoleculesAction());
    m_agateM->addAction(app->manageDrugsAction());
    m_agateM->addAction(app->managePrescribeableDrugsAction());
    m_agateM->addAction(app->managePrescribeableDrugsCompositionAction());
    m_agateM->addSeparator();
    m_agateM->addAction(app->manageSexesAction());
    m_agateM->addAction(app->manageUnitsAction());
    m_agateM->addAction(app->manageAgeClassesAction());
    m_agateM->addSeparator();
}

void MainWindow::createCriminologyMenu(DataCollector *app)
{
    m_criminologyM = new QMenu(tr("&Criminology"), this);

    m_criminologyM->addSeparator();
    m_criminologyM->addAction(app->manageCrimeCasesAction());
    m_criminologyM->addSeparator();
    m_criminologyM->addAction(app->manageInformationSourceTypesAction());
    m_criminologyM->addAction(app->manageJobsAction());
    m_criminologyM->addAction(app->manageProcessingStatesAction());
    m_criminologyM->addAction(app->manageSexesAction());
    m_criminologyM->addAction(app->manageCountriesAction());
    m_criminologyM->addAction(app->manageCitiesAction());
    m_criminologyM->addAction(app->manageHousingTypesAction());
    m_criminologyM->addAction(app->manageWeaponTypesAction());
    m_criminologyM->addAction(app->manageWeaponsAction());
    m_criminologyM->addAction(app->manageModusOperandiAction());
    m_criminologyM->addAction(app->manageCrimeTypesAction());
    m_criminologyM->addAction(app->manageCrimeCasePartyRolesAction());
    m_criminologyM->addAction(app->manageCrimeMotivesAction());
    m_criminologyM->addAction(app->manageMentalDiseasesAction());
    m_criminologyM->addAction(app->manageConsultancyResultsAction());
}

void MainWindow::createStatisticsMenu(DataCollector* app)
{
    m_statisticsM = new QMenu(tr("&Statistics"), this);
    m_statisticsM->addAction(app->showAllStatisticsAction());
}

void MainWindow::createHelpMenu(DataCollector* app)
{
    m_helpM = new QMenu(tr("&Help"), this);
    m_helpM->addAction(app->aboutProgramAction());
    m_helpM->addSeparator();
    m_helpM->addAction(app->aboutQtAction());
}

void MainWindow::initMenues()
{
    auto app = DataCollector::get();

    createFileMenu(app);
    createDatabaseMenu(app);
    createAdminMenu(app);
    createProjectMenu(app);
    createPharmacologyMenu(app);
    createAgateMenu(app);
    createStatisticsMenu(app);
    createCriminologyMenu(app);
    createAgateMenu(app);
    createHelpMenu(app);

    menuBar()->addMenu(m_fileM);
    menuBar()->addMenu(m_databaseM);
    menuBar()->addMenu(m_adminM);
    menuBar()->addMenu(m_projectM);
    menuBar()->addMenu(m_pharmacologyM);
    menuBar()->addMenu(m_criminologyM);
    menuBar()->addMenu(m_agateM);
    menuBar()->addMenu(m_statisticsM);
    menuBar()->addSeparator();
    menuBar()->addMenu(m_helpM);
}

void MainWindow::initStatusBar()
{
    statusBar()->addPermanentWidget(new DatabaseConnectionStatusLabel(statusBar()));
}
