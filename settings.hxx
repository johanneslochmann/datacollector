#pragma once

#include "databaseconnectiondata.hxx"

class Settings
{
public:
    Settings();
    virtual ~Settings();

    void save(const DatabaseConnectionData& cd);
    void save(const QString& translationFileName);

    DatabaseConnectionData loadDatabaseConnectionData();
    QString translationFileName();
};

