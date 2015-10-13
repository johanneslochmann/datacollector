#pragma once

#include "databaseconnectionawareaction.hxx"

class ActionEnabledIfNotConnectedToDatabase : public DatabaseConnectionAwareAction
{
    Q_OBJECT
public:
    ActionEnabledIfNotConnectedToDatabase(const QString& text, QObject* parent, const QString& shortcut = "");
    ActionEnabledIfNotConnectedToDatabase(const QString& text, QObject* parent, const QKeySequence& seq);

protected:
    void adjustStatus(bool isConnected) override;
};
