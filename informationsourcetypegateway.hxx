#pragma once

#include "datagateway.h"

#include "informationsourcetype.hxx"

class InformationSourceTypeGateway : public DataGateway<InformationSourceType>
{
public:
    InformationSourceTypeGateway() : DataGateway<InformationSourceType>() {}

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
