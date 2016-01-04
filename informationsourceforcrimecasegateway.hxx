#pragma once

#include "datagateway.h"

#include "informationsourceforcrimecase.hxx"

class CrimeCase;
using CrimeCaseSPtr = std::shared_ptr<CrimeCase>;

class InformationSourceForCrimeCaseGateway : public DataGateway<InformationSourceForCrimeCase>
{
public:
    InformationSourceForCrimeCaseGateway() : DataGateway<InformationSourceForCrimeCase>() {}

    void loadAllInCrimeCase(CrimeCaseSPtr c);
    void remove(int id);

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
