#pragma once

#include <QString>

class NameIdPair
{
public:
    NameIdPair(const QString& name = "", int id = 0);

    QString name() const;
    int id() const;

    void setName(const QString &name);
    void setId(int id);

private:
    QString m_name { "" };
    int m_id { 0 };
};
