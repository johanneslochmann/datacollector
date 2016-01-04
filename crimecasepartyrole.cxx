#include "crimecasepartyrole.hxx"


CrimeCasePartyRole::CrimeCasePartyRole()
    : Storable() {
}

QString CrimeCasePartyRole::name() const
{
    return m_name;
}

void CrimeCasePartyRole::setName(const QString &name)
{
    m_name = name;
}

QString CrimeCasePartyRole::description() const
{
    return m_description;
}

void CrimeCasePartyRole::setDescription(const QString &description)
{
    m_description = description;
}
