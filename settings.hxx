#pragma once

#include "databaseconnectiondata.hxx"

class Settings
{
public:
    Settings();
    virtual ~Settings();

    void save(const DatabaseConnectionData& cd);

    DatabaseConnectionData loadDatabaseConnectionData();
};

