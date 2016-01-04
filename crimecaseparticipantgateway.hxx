#pragma once

#include "datagateway.h"

#include "crimecaseparticipant.hxx"

class CrimeCaseParticipantGateway: public DataGateway<CrimeCaseParticipant>
{
public:
    CrimeCaseParticipantGateway();

    CrimeCaseParticipantSPtrVector crimeCaseParticipantsInCrimeCase(int crimeCaseId);

protected:
    QString loadAllQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
