#include "crimetype.hxx"


CrimeType::CrimeType()
    : Storable() {
}

QString CrimeType::name() const
{
    return m_name;
}

void CrimeType::setName(const QString &name)
{
    m_name = name;
}

QString CrimeType::description() const
{
    return m_description;
}

void CrimeType::setDescription(const QString &description)
{
    m_description = description;
}
