#include "crimemotive.hxx"


CrimeMotive::CrimeMotive()
    : Storable() {
}

QString CrimeMotive::name() const
{
    return m_name;
}

void CrimeMotive::setName(const QString &name)
{
    m_name = name;
}

QString CrimeMotive::description() const
{
    return m_description;
}

void CrimeMotive::setDescription(const QString &description)
{
    m_description = description;
}
