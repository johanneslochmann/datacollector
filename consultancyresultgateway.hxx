#pragma once

#include "datagateway.h"

#include "consultancyresult.hxx"

class ConsultancyResultGateway : public DataGateway<ConsultancyResult>
{
public:
    ConsultancyResultGateway() : DataGateway<ConsultancyResult>() {}

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
