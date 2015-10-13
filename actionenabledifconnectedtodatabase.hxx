#pragma once

#include "databaseconnectionawareaction.hxx"

class ActionEnabledIfConnectedToDatabase : public DatabaseConnectionAwareAction
{
    Q_OBJECT
public:
    ActionEnabledIfConnectedToDatabase(const QString& text, QObject* parent, const QString& shortcut = "");
    ActionEnabledIfConnectedToDatabase(const QString& text, QObject* parent, const QKeySequence& seq);

protected:
    void adjustStatus(bool isConnected) override;
};
