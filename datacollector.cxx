#include "datacollector.hxx"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>

#include "actionenabledifconnectedtodatabase.hxx"
#include "actionenabledifnotconnectedtodatabase.hxx"
#include "databaseconnectiondatadialog.hxx"
#include "databaseerror.hxx"

DataCollector *DataCollector::get()
{
    return qobject_cast<DataCollector*>(qApp);
}

DataCollector::DataCollector(int &argc, char **argv)
    : QApplication(argc, argv)
{
    initActions();
}

DataCollector::~DataCollector()
{
    closeDatabase();
}

QSqlQuery DataCollector::prepareAndPerformQuery(const QString &sql)
{
    auto qry = prepareQuery(sql);
    performQuery(qry);
    return qry;
}

QSqlQuery DataCollector::prepareQuery(const QString &sql)
{
    QSqlQuery qry(QSqlDatabase::database(databaseConnectionName));

    if (!qry.prepare(sql)) {
        throw DatabaseError(qry.lastError());
    }

    return qry;
}

void DataCollector::performQuery(QSqlQuery &qry)
{
    if (!qry.exec()) {
        throw DatabaseError(qry.lastError());
    }
}

QSqlDatabase DataCollector::database()
{
    return QSqlDatabase::database(databaseConnectionName);
}

void DataCollector::openDatabase()
{
    emit databaseUnavailable();

    auto dlg = new DatabaseConnectionDataDialog(activeWindow());

    if (QDialog::Accepted != dlg->exec()) {
        return;
    }

    if (QSqlDatabase::contains(databaseConnectionName)) {
        closeDatabase();
    }

    auto db = QSqlDatabase::addDatabase("QPSQL", databaseConnectionName);
    db.setHostName(dlg->connectionData().host());
    db.setPort(dlg->connectionData().port());
    db.setDatabaseName(dlg->connectionData().database());
    db.setUserName(dlg->connectionData().userName());
    db.setPassword(dlg->connectionData().password());

    if (db.open()) {
        emit databaseAvailable();
        return;
    }

    emit databaseUnavailable();

    QMessageBox::critical(activeWindow(),
                          tr("Failed to connect to database"),
                          tr("<p><b>Failed to connect to database:</b>/<p><p>%1</p>")
                          .arg(db.lastError().text()));
}

void DataCollector::closeDatabase()
{
    if (QSqlDatabase::contains(databaseConnectionName)) {
        QSqlDatabase::removeDatabase(databaseConnectionName);
    }

    emit databaseUnavailable();
}

void DataCollector::pingDatabase()
{
    try {
        auto qry = prepareAndPerformQuery("select current_timestamp::text;");

        if (!qry.next()) {
            QMessageBox::critical(activeWindow(),
                                  tr("Ping Failed"),
                                  tr("Ping failed: no rows returned."));
            qry.clear();
            return;
        }

        QMessageBox::information(activeWindow(),
                                 tr("Pink OK"),
                                 tr("<p>Server Timestamp: %1</p>").arg(qry.value(0).toString()));
    }
    catch(DatabaseError& e) {
        QMessageBox::critical(activeWindow(),
                              tr("Failed to ping database"),
                              tr("<p><b>Failed to ping database:</b></p><p>Server Timestamp: %1</p>")
                              .arg(e.error().text()));
    }
}

void DataCollector::aboutProgram()
{

}

void DataCollector::initActions()
{
    m_quit = new QAction(tr("&Quit"), this);
    m_quit->setShortcut(QKeySequence::Quit);
    connect(m_quit, &QAction::triggered, this, &DataCollector::quit);

    m_openDatabase = new ActionEnabledIfNotConnectedToDatabase(tr("&Connect..."), this, QKeySequence::Open);
    connect(m_openDatabase, &QAction::triggered, this, &DataCollector::openDatabase);

    m_closeDatabase = new ActionEnabledIfConnectedToDatabase(tr("C&lose"), this, QKeySequence::Close);
    connect(m_closeDatabase, &QAction::triggered, this, &DataCollector::closeDatabase);

    m_pingDatabase = new ActionEnabledIfConnectedToDatabase(tr("&Ping"), this);
    connect(m_pingDatabase, &QAction::triggered, this, &DataCollector::pingDatabase);

    m_aboutProgram = new QAction(tr("&About this program..."), this);
    connect(m_aboutProgram, &QAction::triggered, this, &DataCollector::aboutProgram);

    m_aboutQt = new QAction(tr("&About Qt..."), this);
    connect(m_aboutQt, &QAction::triggered, this, &DataCollector::aboutQt);

    m_manageChannelsIntoPatient = new ActionEnabledIfConnectedToDatabase(tr("Channels Into Patient..."), this);
    connect(m_manageChannelsIntoPatient, &QAction::triggered, this, &DataCollector::manageChannelsIntoPatient);

    m_manageDrugAdministrationMethods = new ActionEnabledIfConnectedToDatabase(tr("Drug Administration Methods..."), this);
    connect(m_manageDrugAdministrationMethods, &QAction::triggered, this, &DataCollector::manageDrugAdministrationMethods);

    m_manageMoleculeClasses = new ActionEnabledIfConnectedToDatabase(tr("Molecule Classes..."), this);
    connect(m_manageMoleculeClasses, &QAction::triggered, this, &DataCollector::manageMoleculeClasses);

    m_manageMolecules = new ActionEnabledIfConnectedToDatabase(tr("Molecules"), this);
    connect(m_manageMolecules, &QAction::triggered, this, &DataCollector::manageMolecules);

    m_manageSexes = new ActionEnabledIfConnectedToDatabase(tr("Sexes"), this);
    connect(m_manageSexes, &QAction::triggered, this, &DataCollector::manageSexes);

    m_manageUnits = new ActionEnabledIfConnectedToDatabase(tr("Units"), this);
    connect(m_manageUnits, &QAction::triggered, this, &DataCollector::manageUnits);

    m_manageProjects = new ActionEnabledIfConnectedToDatabase(tr("Projects"), this);
    connect(m_manageProjects, &QAction::triggered, this, &DataCollector::manageProjects);

    m_manageCampaigns = new ActionEnabledIfConnectedToDatabase(tr("Campaigns"), this);
    connect(m_manageCampaigns, &QAction::triggered, this, &DataCollector::manageCampaigns);

    m_manageProbands = new ActionEnabledIfConnectedToDatabase(tr("Probands"), this);
    connect(m_manageProbands, &QAction::triggered, this, &DataCollector::manageProbands);
}
