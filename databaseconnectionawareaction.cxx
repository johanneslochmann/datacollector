#include "databaseconnectionawareaction.hxx"

#include "datacollector.hxx"

DatabaseConnectionAwareAction::DatabaseConnectionAwareAction(const QString &name, QObject *p, const QString &shortcut)
    : QAction(name, p)
{
    if (!shortcut.isEmpty()) {
        setShortcut(shortcut);
    }

    connect(DataCollector::get(), &DataCollector::databaseAvailable, this, &DatabaseConnectionAwareAction::databaseAvailable);
    connect(DataCollector::get(), &DataCollector::databaseUnavailable, this, &DatabaseConnectionAwareAction::databaseUnavailable);
}

DatabaseConnectionAwareAction::DatabaseConnectionAwareAction(const QString &name, QObject *p, const QKeySequence &seq)
    : QAction(name, p)
{
    setShortcut(seq);

    connect(DataCollector::get(), &DataCollector::databaseAvailable, this, &DatabaseConnectionAwareAction::databaseAvailable);
    connect(DataCollector::get(), &DataCollector::databaseUnavailable, this, &DatabaseConnectionAwareAction::databaseUnavailable);
}

void DatabaseConnectionAwareAction::databaseAvailable()
{
    adjustStatus(true);
}

void DatabaseConnectionAwareAction::databaseUnavailable()
{
    adjustStatus(false);
}

