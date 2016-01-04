#pragma once

#include "datagateway.h"

#include "crimemotive.hxx"

class CrimeMotiveGateway : public DataGateway<CrimeMotive>
{
public:
    CrimeMotiveGateway() : DataGateway<CrimeMotive>() {}

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
