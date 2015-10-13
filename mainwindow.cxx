#include "mainwindow.hxx"

#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

#include "datacollector.hxx"
#include "databaseconnectionstatuslabel.hxx"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initMenues();
    initStatusBar();
}

MainWindow::~MainWindow()
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

    QMenu* help = new QMenu(tr("&Help"), this);
    help->addAction(app->aboutProgramAction());
    help->addSeparator();
    help->addAction(app->aboutQtAction());

    menuBar()->addMenu(file);
    menuBar()->addMenu(db);
    menuBar()->addSeparator();
    menuBar()->addMenu(help);
}

void MainWindow::initStatusBar()
{
    statusBar()->addPermanentWidget(new DatabaseConnectionStatusLabel(statusBar()));
}
