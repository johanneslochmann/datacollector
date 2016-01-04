#pragma once

#include "datagateway.h"

#include "modusoperandi.hxx"

class ModusOperandiGateway : public DataGateway<ModusOperandi>
{
public:
    ModusOperandiGateway() : DataGateway<ModusOperandi>() {}

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
