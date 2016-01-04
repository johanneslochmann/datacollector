#include "crimecaseparticipant.hxx"

#include "crimecase.hxx"

CrimeCaseParticipant::CrimeCaseParticipant()
    : Storable(), m_crimeCase(std::make_shared<CrimeCase>())
{
}

CrimeCaseSPtr CrimeCaseParticipant::crimeCase() const
{
    return m_crimeCase;
}

void CrimeCaseParticipant::setCrimeCase(const CrimeCaseSPtr &crimeCase)
{
    m_crimeCase = crimeCase;
}

QString CrimeCaseParticipant::name() const
{
    return m_name;
}

void CrimeCaseParticipant::setName(const QString &name)
{
    m_name = name;
}

int CrimeCaseParticipant::ageInYears() const
{
    return m_ageInYears;
}

void CrimeCaseParticipant::setAgeInYears(int ageInYears)
{
    m_ageInYears = ageInYears;
}

QString CrimeCaseParticipant::description() const
{
    return m_description;
}

void CrimeCaseParticipant::setDescription(const QString &description)
{
    m_description = description;
}

CrimeCasePartyRoleSPtr CrimeCaseParticipant::role() const
{
    return m_role;
}

void CrimeCaseParticipant::setRole(const CrimeCasePartyRoleSPtr &role)
{
    m_role = role;
}

SexSPtr CrimeCaseParticipant::sex() const
{
    return m_sex;
}

void CrimeCaseParticipant::setSex(const SexSPtr &sex)
{
    m_sex = sex;
}
