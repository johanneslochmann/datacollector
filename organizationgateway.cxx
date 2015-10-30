#include "organizationgateway.hxx"

QString OrganizationGateway::loadAllQueryText() const
{
    return "select name, description, id from core.organization_unit order by name asc;";
}

void OrganizationGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
