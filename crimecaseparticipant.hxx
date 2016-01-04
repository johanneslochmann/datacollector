#pragma once

#include "storable.hxx"

class CrimeCase;

using CrimeCaseSPtr = std::shared_ptr<CrimeCase>;

class CrimeCaseParticipant;
using CrimeCaseParticipantSPtr = std::shared_ptr<CrimeCaseSPtr>;
using CrimeCaseParticipantSPtrVector = std::vector<CrimeCaseParticipantSPtr>;

class CrimeCaseParticipant : public Storable
{
public:
    CrimeCaseParticipant();

    CrimeCaseSPtr crimeCase() const;
    void setCrimeCase(const CrimeCaseSPtr &crimeCase);

private:
    CrimeCaseSPtr m_crimeCase;
};
