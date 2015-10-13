#include "databaseconnectiondata.hxx"

DatabaseConnectionData::DatabaseConnectionData()
{

}

QString DatabaseConnectionData::host() const
{
    return m_host;
}

void DatabaseConnectionData::setHost(const QString &host)
{
    m_host = host;
}

int DatabaseConnectionData::port() const
{
    return m_port;
}

void DatabaseConnectionData::setPort(int port)
{
    m_port = port;
}

QString DatabaseConnectionData::database() const
{
    return m_database;
}

void DatabaseConnectionData::setDatabase(const QString &database)
{
    m_database = database;
}

QString DatabaseConnectionData::userName() const
{
    return m_userName;
}

void DatabaseConnectionData::setUserName(const QString &userName)
{
    m_userName = userName;
}

QString DatabaseConnectionData::password() const
{
    return m_password;
}

void DatabaseConnectionData::setPassword(const QString &password)
{
    m_password = password;
}

