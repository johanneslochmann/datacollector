#pragma once

#include "datagateway.h"

#include "city.hxx"

class CityGateway : public DataGateway<City>
{
public:
    CityGateway() : DataGateway<City>() {}

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
