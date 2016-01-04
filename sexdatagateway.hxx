#pragma once

#include "datagateway.h"

#include "sex.hxx"

class SexDataGateway: public DataGateway<Sex>
{
public:
    SexDataGateway(): DataGateway<Sex>()
    {}

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<Sex> t, const QSqlRecord &rec) override;
};


