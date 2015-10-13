#include "databaseerror.hxx"

DatabaseError::DatabaseError(const QSqlError &err)
    : m_error(err)
{
}

