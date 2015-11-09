#include "sex.hxx"

Sex::Sex()
    : Storable()
{
}

QString Sex::name() const
{
    return m_name;
}

QString Sex::description() const
{
    return m_description;
}

void Sex::setName(const QString &name)
{
    m_name = name;
}

void Sex::setDescription(const QString &description)
{
    m_description = description;
}

