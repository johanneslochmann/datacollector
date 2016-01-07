#include "datacollector.hxx"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include <QFile>

#include "actionenabledifconnectedtodatabase.hxx"
#include "actionenabledifnotconnectedtodatabase.hxx"
#include "databaseconnectiondatadialog.hxx"
#include "databaseerror.hxx"
#include "aboutdatacollectordialog.hxx"
#include "settings.hxx"

DataCollector *DataCollector::get()
{
    return qobject_cast<DataCollector*>(qApp);
}

DataCollector::DataCollector(int &argc, char **argv)
    : QApplication(argc, argv)
{
    initActions();
    loadTranslations();
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
    if (!QSqlDatabase::database(databaseConnectionName).transaction()) {
        throw DatabaseError(QSqlDatabase::database(databaseConnectionName).lastError());
    }
}

void DataCollector::commit()
{
    if (!QSqlDatabase::database(databaseConnectionName).commit()) {
        throw DatabaseError(QSqlDatabase::database(databaseConnectionName).lastError());
    }
}

void DataCollector::rollback()
{
    if (!QSqlDatabase::database(databaseConnectionName).rollback()) {
        showDatabaseError(DatabaseError(QSqlDatabase::database(databaseConnectionName).lastError()),
                          tr("Failed to rollback database transaction. Program will terminate."),
                          activeWindow());
        quit();
    }
}

void DataCollector::performQuery(QSqlQuery &qry, bool createTransaction)
{
    if (createTransaction) {
        begin();
    }

    QMapIterator<QString, QVariant> i(qry.boundValues());
    while (i.hasNext()) {
        i.next();
    }

    if (!qry.exec()) {
        throw DatabaseError(qry.lastError());
    }
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
    auto dlg = new AboutDataCollectorDialog(activeWindow());
    dlg->exec();
}

void DataCollector::reloadTranslation()
{
    loadTranslations();
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

    m_settings = new QAction(tr("&Settings..."), this);
    connect(m_settings, &QAction::triggered, this, &DataCollector::manageSettings);

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

    m_showAllStatistics = new ActionEnabledIfConnectedToDatabase(tr("Show All Statistics"), this);
    connect(m_showAllStatistics, &QAction::triggered, this, &DataCollector::showAllStatistics);

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

    m_manageWeapons = new ActionEnabledIfConnectedToDatabase(tr("Weapons"), this);
    connect(m_manageWeapons, &QAction::triggered, this, &DataCollector::manageWeapons);

    m_manageCities = new ActionEnabledIfConnectedToDatabase(tr("Cities"), this);
    connect(m_manageCities, &QAction::triggered, this, &DataCollector::manageCities);

    m_manageCrimeCases = new ActionEnabledIfConnectedToDatabase(tr("Crime Cases"), this);
    connect(m_manageCrimeCases, &QAction::triggered, this, &DataCollector::manageCrimeCases);

    m_manageProcessingStates = new ActionEnabledIfConnectedToDatabase(tr("Processing States"), this);
    connect(m_manageProcessingStates, &QAction::triggered, this, &DataCollector::manageProcessingStates);
}

void DataCollector::loadTranslations()
{
    auto currentLocale = Settings().loadLocale();

    if (currentLocale.isEmpty()) {
        return;
    }

    QString path(":/translations");
    auto qmFileName = QString("%1.%2.qm").arg(applicationName()).arg(currentLocale);

    QFile qmF(path + "/" + qmFileName);

    if (!qmF.exists()) {
        QMessageBox::critical(activeWindow(), tr("Translation file not found"),
                              tr("Translation file %1 does not exist.").arg(qmF.fileName()));
        return;
    }

    if (!m_translator.load(qmFileName, path)) {
        QMessageBox::critical(activeWindow(),
                              tr("Failed to load locale"), tr("Failed to load locale file '%1' from '%2'.")
                              .arg(qmFileName)
                              .arg(path));
        return;
    }

    installTranslator(&m_translator);
}
