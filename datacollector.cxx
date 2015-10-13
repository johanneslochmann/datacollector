#include "datacollector.hxx"

#include "actionenabledifconnectedtodatabase.hxx"
#include "actionenabledifnotconnectedtodatabase.hxx"

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

}

void DataCollector::openDatabase()
{

}

void DataCollector::closeDatabase()
{

}

void DataCollector::pingDatabase()
{

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
    connect(m_closeDatabase, &QAction::triggered, this, &DataCollector::closeDatabaseAction);

    m_pingDatabase = new ActionEnabledIfConnectedToDatabase(tr("&Ping"), this);
    connect(m_pingDatabase, &QAction::triggered, this, &DataCollector::pingDatabase);

    m_aboutProgram = new QAction(tr("&About this program..."), this);
    connect(m_aboutProgram, &QAction::triggered, this, &DataCollector::aboutProgram);

    m_aboutQt = new QAction(tr("&About Qt..."), this);
    connect(m_aboutQt, &QAction::triggered, this, &DataCollector::aboutQt);
}
