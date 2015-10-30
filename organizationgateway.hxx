#pragma once

#include "datagateway.h"

#include "organization.hxx"

class OrganizationGateway : public DataGateway<Organization>
{
public:
    OrganizationGateway() : DataGateway<Organization>() {}

protected:
    QString loadAllQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
