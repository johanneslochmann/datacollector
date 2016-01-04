#pragma once

#include "datagateway.h"

#include "mentaldisease.hxx"

class MentalDiseaseGateway : public DataGateway<MentalDisease>
{
public:
    MentalDiseaseGateway() : DataGateway<MentalDisease>() {}

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
