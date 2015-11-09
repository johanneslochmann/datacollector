#include "nameidpair.hxx"

NameIdPair::NameIdPair(const QString &name, int id)
    : m_name(name), m_id(id)
{
}

QString NameIdPair::name() const
{
    return m_name;
}

void NameIdPair::setName(const QString &name)
{
    m_name = name;
}

int NameIdPair::id() const
{
    return m_id;
}

void NameIdPair::setId(int id)
{
    m_id = id;
}

