#include "actionenabledifnotconnectedtodatabase.hxx"

ActionEnabledIfNotConnectedToDatabase::ActionEnabledIfNotConnectedToDatabase(const QString &text, QObject *parent, const QString &shortcut)
    : DatabaseConnectionAwareAction(text, parent, shortcut)
{
    adjustStatus(false);
}

ActionEnabledIfNotConnectedToDatabase::ActionEnabledIfNotConnectedToDatabase(const QString &text, QObject *parent, const QKeySequence &seq)
    : DatabaseConnectionAwareAction(text, parent, seq)
{
    adjustStatus(false);
}

void ActionEnabledIfNotConnectedToDatabase::adjustStatus(bool isConnected)
{
    setEnabled(!isConnected);
}

