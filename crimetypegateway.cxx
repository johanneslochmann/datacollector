#include "crimetypegateway.hxx"

QString CrimeTypeGateway::loadAllQueryText() const
{
    return "select name, description, id from forensics.crime_type order by name asc;";
}

QString CrimeTypeGateway::loadByIdQueryText() const
{
    return "select name, description, id from forensics.crime_type where id = :id;";
}

void CrimeTypeGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
