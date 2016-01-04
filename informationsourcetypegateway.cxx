#include "informationsourcetypegateway.hxx"

QString InformationSourceTypeGateway::loadAllQueryText() const
{
    return "select name, description, id from core.information_source_type order by name asc;";
}

QString InformationSourceTypeGateway::loadByIdQueryText() const
{
    return "select name, description, id from core.information_source_type where id = :id;";
}

void InformationSourceTypeGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
