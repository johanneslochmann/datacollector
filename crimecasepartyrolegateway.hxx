#pragma once

#include "datagateway.h"

#include "crimecasepartyrole.hxx"

class CrimeCasePartyRoleGateway : public DataGateway<CrimeCasePartyRole>
{
public:
    CrimeCasePartyRoleGateway() : DataGateway<CrimeCasePartyRole>() {}

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
