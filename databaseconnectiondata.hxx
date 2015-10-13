#pragma once

#include <QString>

const QString defaultDatabaseHostName { "localhost" };
const int defaultDatabasePort { 5432 };
const QString defaultDatabaseName { "" };
const QString defaultDatabaseUserName { "" };
const QString defaultDatabasePassword { "" };

class DatabaseConnectionData
{
public:
    DatabaseConnectionData();

    QString host() const;
    int port() const;
    QString database() const;
    QString userName() const;
    QString password() const;

    void setHost(const QString &host);
    void setPort(int port);
    void setDatabase(const QString &database);
    void setUserName(const QString &userName);
    void setPassword(const QString &password);

private:
    QString m_host { defaultDatabaseHostName };
    int m_port { defaultDatabasePort };
    QString m_database { defaultDatabaseName };
    QString m_userName { defaultDatabaseUserName };
    QString m_password { defaultDatabasePassword };
};
