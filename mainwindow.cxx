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

void MainWindow::initMenues()
{
    auto app = DataCollector::get();

    QMenu* file = new QMenu(tr("&File"), this);
    file->addAction(app->quitAction());

    QMenu* db = new QMenu(tr("&Database"), this);
    db->addAction(app->openDatabaseAction());
    db->addAction(app->closeDatabaseAction());
    db->addSeparator();
    db->addAction(app->pingDatabaseAction());

    QMenu* coreData = new QMenu(tr("&Core Data"), this);
    coreData->addAction(app->manageProbandsAction());
    coreData->addSeparator();
    coreData->addAction(app->manageProjectsAction());
    coreData->addAction(app->manageCampaignsAction());
    coreData->addSeparator();
    coreData->addAction(app->manageOrganizationUnitsAction());
    coreData->addAction(app->manageIcd10DiagnosisAction());
    coreData->addSeparator();
    coreData->addAction(app->manageChannelsIntoPatientAction());
    coreData->addAction(app->manageDrugAdministrationMethodsAction());
    coreData->addAction(app->manageMoleculeClassesAction());
    coreData->addAction(app->manageMoleculesAction());
    coreData->addAction(app->manageDrugsAction());
    coreData->addAction(app->managePrescribeableDrugsAction());
    coreData->addAction(app->managePrescribeableDrugsCompositionAction());
    coreData->addSeparator();
    coreData->addAction(app->manageSexesAction());
    coreData->addAction(app->manageUnitsAction());
    coreData->addSeparator();
    coreData->addAction(app->manageSurveysAction());

    QMenu* dataEntry = new QMenu(tr("&Surveys"), this);
    dataEntry->addAction(app->manageSurveyDataAction());

    QMenu* help = new QMenu(tr("&Help"), this);
    help->addAction(app->aboutProgramAction());
    help->addSeparator();
    help->addAction(app->aboutQtAction());

    menuBar()->addMenu(file);
    menuBar()->addMenu(db);
    menuBar()->addMenu(coreData);
    menuBar()->addMenu(dataEntry);
    menuBar()->addSeparator();
    menuBar()->addMenu(help);
}

void MainWindow::initStatusBar()
{
    statusBar()->addPermanentWidget(new DatabaseConnectionStatusLabel(statusBar()));
}
