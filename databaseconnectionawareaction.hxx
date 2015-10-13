#pragma once

#include <QAction>

class DatabaseConnectionAwareAction : public QAction
{
    Q_OBJECT
public:
    DatabaseConnectionAwareAction(const QString& name = "", QObject* p = nullptr, const QString& shortcut = "");
    DatabaseConnectionAwareAction(const QString& name, QObject* p, const QKeySequence& seq);

public slots:
    void databaseAvailable();
    void databaseUnavailable();

protected:
    virtual void adjustStatus(bool isConnected) = 0;
};
