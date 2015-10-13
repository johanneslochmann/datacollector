#include "actionenabledifconnectedtodatabase.hxx"

ActionEnabledIfConnectedToDatabase::ActionEnabledIfConnectedToDatabase(const QString &text, QObject *parent, const QString &shortcut)
    : DatabaseConnectionAwareAction(text, parent, shortcut)
{
    adjustStatus(false);
}

ActionEnabledIfConnectedToDatabase::ActionEnabledIfConnectedToDatabase(const QString &text, QObject *parent, const QKeySequence &seq)
    : DatabaseConnectionAwareAction(text, parent, seq)
{
    adjustStatus(false);
}

void ActionEnabledIfConnectedToDatabase::adjustStatus(bool isConnected)
{
    setEnabled(isConnected);
}
