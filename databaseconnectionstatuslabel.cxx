#include "databaseconnectionstatuslabel.hxx"

#include "datacollector.hxx"

DatabaseConnectionStatusLabel::DatabaseConnectionStatusLabel(QWidget *p)
    : QLabel(p)
{
    connect(DataCollector::get(), &DataCollector::databaseAvailable, this, &DatabaseConnectionStatusLabel::databaseAvailable);
    connect(DataCollector::get(), &DataCollector::databaseUnavailable, this, &DatabaseConnectionStatusLabel::databaseUnavailable);

    databaseUnavailable();
}

void DatabaseConnectionStatusLabel::databaseAvailable()
{
    setText(tr("Connected."));
}

void DatabaseConnectionStatusLabel::databaseUnavailable()
{
    setText(tr("Not Connected."));
}

