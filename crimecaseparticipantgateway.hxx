#pragma once

#include "datagateway.h"

#include "crimecaseparticipant.hxx"

class CrimeCaseParticipantGateway: public DataGateway<CrimeCaseParticipant>
{
public:
    CrimeCaseParticipantGateway();

    void loadAllInCrimeCase(CrimeCaseSPtr crimeCase);
    void remove(int id);
    void save(CrimeCaseParticipantSPtr c);

    void loadSubRecords(CrimeCaseParticipantSPtr c);

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;

    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;

    void insert(CrimeCaseParticipantSPtr c);
    void update(CrimeCaseParticipantSPtr c);
};
