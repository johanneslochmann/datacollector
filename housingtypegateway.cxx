#include "housingtypegateway.hxx"

QString HousingTypeGateway::loadAllQueryText() const
{
    return "select name, description, id from geo.housing_type order by name asc;";
}

QString HousingTypeGateway::loadByIdQueryText() const
{
    return "select name, description, id from geo.housing_type where id = :id;";
}

void HousingTypeGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
