#include "citygateway.hxx"

QString CityGateway::loadAllQueryText() const
{
    return "select name, description, id from geo.city order by name asc;";
}

QString CityGateway::loadByIdQueryText() const
{
    return "select name, description, id from geo.city where id = :id;";
}

void CityGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
