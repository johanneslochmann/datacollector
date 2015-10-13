#include "settings.hxx"

#include <QSettings>

Settings::Settings()
{    
}

Settings::~Settings()
{
}

void Settings::save(const DatabaseConnectionData &cd)
{
    QSettings s;
    s.beginGroup("DatabaseConnectionData");
    s.setValue("HostName", cd.host());
    s.setValue("Port", cd.port());
    s.setValue("DatabaseName", cd.database());
    s.setValue("UserName", cd.userName());
}

DatabaseConnectionData Settings::loadDatabaseConnectionData()
{
    QSettings s;
    s.beginGroup("DatabaseConnectionData");;

    DatabaseConnectionData cd;

    cd.setHost(s.value("HostName", defaultDatabaseHostName).toString());
    cd.setPort(s.value("Port", defaultDatabasePort).toInt());
    cd.setDatabase(s.value("DatabaseName", defaultDatabaseName).toString());
    cd.setUserName(s.value("UserName", defaultDatabaseUserName).toString());

    return cd;
}

