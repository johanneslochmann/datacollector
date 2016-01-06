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

CrimeTypeSPtr CrimeCaseParticipant::crimeType() const
{
    return m_crimeType;
}

void CrimeCaseParticipant::setCrimeType(const CrimeTypeSPtr &crimeType)
{
    m_crimeType = crimeType;
}

JobSPtr CrimeCaseParticipant::job() const
{
    return m_job;
}

void CrimeCaseParticipant::setJob(const JobSPtr &job)
{
    m_job = job;
}

CrimeMotiveSPtr CrimeCaseParticipant::motive() const
{
    return m_motive;
}

void CrimeCaseParticipant::setMotive(const CrimeMotiveSPtr &motive)
{
    m_motive = motive;
}

MentalDiseaseSPtr CrimeCaseParticipant::mentalDisease() const
{
    return m_mentalDisease;
}

void CrimeCaseParticipant::setMentalDisease(const MentalDiseaseSPtr &mentalDisease)
{
    m_mentalDisease = mentalDisease;
}

ModusOperandiSPtr CrimeCaseParticipant::modusOperandi() const
{
    return m_modusOperandi;
}

void CrimeCaseParticipant::setModusOperandi(const ModusOperandiSPtr &modusOperandi)
{
    m_modusOperandi = modusOperandi;
}

WeaponSPtr CrimeCaseParticipant::weapon() const
{
    return m_weapon;
}

void CrimeCaseParticipant::setWeapon(const WeaponSPtr &weapon)
{
    m_weapon = weapon;
}

ConsultancyResultSPtr CrimeCaseParticipant::consultancyResult() const
{
    return m_consultancyResult;
}

void CrimeCaseParticipant::setConsultancyResult(const ConsultancyResultSPtr &consultancyResult)
{
    m_consultancyResult = consultancyResult;
}

bool CrimeCaseParticipant::hasPrecedentConvictions() const
{
    return m_hasPrecedentConvictions;
}

void CrimeCaseParticipant::setHasPrecedentConvictions(bool value)
{
    m_hasPrecedentConvictions = value;
}

bool CrimeCaseParticipant::isDrugIntoxicated() const
{
    return m_isDrugIntoxicated;
}

void CrimeCaseParticipant::setIsDrugIntoxicated(bool isDrugIntoxicated)
{
    m_isDrugIntoxicated = isDrugIntoxicated;
}

bool CrimeCaseParticipant::isAlcoholIntoxicated() const
{
    return m_isAlcoholIntoxicated;
}

void CrimeCaseParticipant::setIsAlcoholIntoxicated(bool isAlcoholIntoxicated)
{
    m_isAlcoholIntoxicated = isAlcoholIntoxicated;
}

bool CrimeCaseParticipant::legallyOwnsWeapon() const
{
    return m_legallyOwnsWeapon;
}

void CrimeCaseParticipant::setLegallyOwnsWeapon(bool legallyOwnsWeapon)
{
    m_legallyOwnsWeapon = legallyOwnsWeapon;
}
