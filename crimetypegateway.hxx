#pragma once

#include "datagateway.h"

#include "crimetype.hxx"

class CrimeTypeGateway : public DataGateway<CrimeType>
{
public:
    CrimeTypeGateway() : DataGateway<CrimeType>() {}

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
