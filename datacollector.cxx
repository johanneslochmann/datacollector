#include "datacollector.hxx"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

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

QSqlQuery DataCollector::prepareAndPerformQuery(const QString &sql, bool createTransaction)
{
    auto qry = prepareQuery(sql);
    performQuery(qry, createTransaction);
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

void DataCollector::begin()
{
    qDebug() << "begin...";
    if (!QSqlDatabase::database(databaseConnectionName).transaction()) {
        throw DatabaseError(QSqlDatabase::database(databaseConnectionName).lastError());
    }
    qDebug() << "in transaction";
}

void DataCollector::commit()
{
    qDebug() << "commit...";
    if (!QSqlDatabase::database(databaseConnectionName).commit()) {
        throw DatabaseError(QSqlDatabase::database(databaseConnectionName).lastError());
    }
    qDebug() << "transaction commited";
}

void DataCollector::rollback()
{
    qDebug() << "rollback...";
    if (!QSqlDatabase::database(databaseConnectionName).rollback()) {
        showDatabaseError(DatabaseError(QSqlDatabase::database(databaseConnectionName).lastError()),
                          tr("Failed to rollback database transaction. Program will terminate."),
                          activeWindow());
        quit();
    }
    qDebug() << "rolled back";
}

void DataCollector::performQuery(QSqlQuery &qry, bool createTransaction)
{
    if (createTransaction) {
        begin();
    }

    qDebug() << "performing query: " << qry.lastQuery();

    QMapIterator<QString, QVariant> i(qry.boundValues());
    while (i.hasNext()) {
        i.next();
        qDebug() << "\t" << i.key() << ": " << i.value().toString();
    }

    if (!qry.exec()) {
        qDebug() << "failed: " << qry.lastError().text();
        throw DatabaseError(qry.lastError());
    }

    qDebug() << "OK";
}

bool DataCollector::performQueryWithExpectedSize(QSqlQuery &qry, int expectedSize, bool createTransaction)
{
    performQuery(qry, createTransaction);

    if (expectedSize != qry.size()) {
        return false;
    }

    return true;
}

QSqlDatabase DataCollector::database()
{
    return QSqlDatabase::database(databaseConnectionName);
}

void DataCollector::showDatabaseError(const DatabaseError &err, const QString &info, QWidget *parent)
{
    QMessageBox::critical((parent ? parent : activeWindow()),
                          (info.isEmpty() ? tr("Database Error") : info),
                          err.error().text());
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
    emit databaseAboutToClose();

    processEvents();

    if (QSqlDatabase::contains(databaseConnectionName)) {
        QSqlDatabase::removeDatabase(databaseConnectionName);
    }

    emit databaseUnavailable();
}

void DataCollector::pingDatabase()
{
    try {
        auto qry = prepareAndPerformQuery("select current_timestamp::text;", false);

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

    m_manageDrugs = new ActionEnabledIfConnectedToDatabase(tr("Drugs"), this);
    connect(m_manageDrugs, &QAction::triggered, this, &DataCollector::manageDrugs);

    m_managePrescribeableDrugs = new ActionEnabledIfConnectedToDatabase(tr("Prescribeable Drugs"), this);
    connect(m_managePrescribeableDrugs, &QAction::triggered, this, &DataCollector::managePrescribeableDrugs);

    m_managePrescribeableDrugsComposition = new ActionEnabledIfConnectedToDatabase(tr("Prescribeable Drugs Composition"), this);
    connect(m_managePrescribeableDrugsComposition, &QAction::triggered, this, &DataCollector::managePrescribeableDrugsComposition);

    m_manageSurveys = new ActionEnabledIfConnectedToDatabase(tr("All Surveys"), this);
    connect(m_manageSurveys, &QAction::triggered, this, &DataCollector::manageSurveys);

    m_manageOrganizationUnits = new ActionEnabledIfConnectedToDatabase(tr("Organization Units"), this);
    connect(m_manageOrganizationUnits, &QAction::triggered, this, &DataCollector::manageOrganizationUnits);

    m_manageIcd10Diagnosis = new ActionEnabledIfConnectedToDatabase(tr("ICD 10 Diagnosis"), this);
    connect(m_manageIcd10Diagnosis, &QAction::triggered, this, &DataCollector::manageIcd10Diagnosis);

    m_manageAgeClasses = new ActionEnabledIfConnectedToDatabase(tr("Age Classes"), this);
    connect(m_manageAgeClasses, &QAction::triggered, this, &DataCollector::manageAgeClasses);

    m_manageSmokingHabits = new ActionEnabledIfConnectedToDatabase(tr("Smoking Habits"), this);
    connect(m_manageSmokingHabits, &QAction::triggered, this, &DataCollector::manageSmokingHabits);

    m_manageCollateralEffects = new ActionEnabledIfConnectedToDatabase(tr("Collateral Effects"), this);
    connect(m_manageCollateralEffects, &QAction::triggered, this, &DataCollector::manageCollateralEffects);

    m_manageSurveyData = new ActionEnabledIfConnectedToDatabase(tr("Manage Generic Survey Data"), this);
    connect(m_manageSurveyData, &QAction::triggered, this, &DataCollector::manageSurveyData);

    m_manageAgateData = new ActionEnabledIfConnectedToDatabase(tr("Manage Agate Data"), this);
    connect(m_manageAgateData, &QAction::triggered, this, &DataCollector::manageAgateData);

    m_showCoreStatistics = new ActionEnabledIfConnectedToDatabase(tr("Show Core Statistics"), this);
    connect(m_showCoreStatistics, &QAction::triggered, this, &DataCollector::showCoreStatistics);

    m_manageCountries = new ActionEnabledIfConnectedToDatabase(tr("Countries"), this);
    connect(m_manageCountries, &QAction::triggered, this, &DataCollector::manageCountries);

    m_manageWeaponTypes = new ActionEnabledIfConnectedToDatabase(tr("Weapon Types"), this);
    connect(m_manageWeaponTypes, &QAction::triggered, this, &DataCollector::manageWeaponTypes);

    m_manageHousingTypes = new ActionEnabledIfConnectedToDatabase(tr("Housing Types"), this);
    connect(m_manageHousingTypes, &QAction::triggered, this, &DataCollector::manageHousingTypes);

    m_manageModusOperandi = new ActionEnabledIfConnectedToDatabase(tr("Modus Operandi"), this);
    connect(m_manageModusOperandi, &QAction::triggered, this, &DataCollector::manageModusOperandi);

    m_manageCrimeTypes = new ActionEnabledIfConnectedToDatabase(tr("Crime Type"), this);
    connect(m_manageCrimeTypes, &QAction::triggered, this, &DataCollector::manageCrimeTypes);

    m_manageInformationSourceTypes = new ActionEnabledIfConnectedToDatabase(tr("Information Source Types"), this);
    connect(m_manageInformationSourceTypes, &QAction::triggered, this, &DataCollector::manageInformationSourceTypes);

    m_manageCrimeCasePartyRoles = new ActionEnabledIfConnectedToDatabase(tr("Crime Case Party Roles"), this);
    connect(m_manageCrimeCasePartyRoles, &QAction::triggered, this, &DataCollector::manageCrimeCasePartyRoles);

    m_manageJobs = new ActionEnabledIfConnectedToDatabase(tr("Jobs"), this);
    connect(m_manageJobs, &QAction::triggered, this, &DataCollector::manageJobs);

    m_manageCrimeMotives = new ActionEnabledIfConnectedToDatabase(tr("Crime Motives"), this);
    connect(m_manageCrimeMotives, &QAction::triggered, this, &DataCollector::manageCrimeMotives);

    m_manageMentalDiseases = new ActionEnabledIfConnectedToDatabase(tr("Mental Diseases"), this);
    connect(m_manageMentalDiseases, &QAction::triggered, this, &DataCollector::manageMentalDiseases);

    m_manageConsultancyResults = new ActionEnabledIfConnectedToDatabase(tr("Consultancy Results"), this);
    connect(m_manageConsultancyResults, &QAction::triggered, this, &DataCollector::manageConsultancyResults);
}
