#pragma once

#include "datagateway.h"

#include "housingtype.hxx"

class HousingTypeGateway : public DataGateway<HousingType>
{
public:
    HousingTypeGateway() : DataGateway<HousingType>() {}

protected:
    QString loadAllQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
