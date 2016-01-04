#include "crimecaseparticipant.hxx"

#include "crimecase.hxx"

CrimeCaseParticipant::CrimeCaseParticipant()
    : Storable()
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
