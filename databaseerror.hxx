#pragma once

#include <QSqlError>

class DatabaseError
{
public:
    explicit DatabaseError(const QSqlError& err);

    QSqlError error() const { return m_error; }

protected:
    QSqlError m_error;
};

