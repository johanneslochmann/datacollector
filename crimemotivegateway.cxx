#include "crimemotivegateway.hxx"

QString CrimeMotiveGateway::loadAllQueryText() const
{
    return "select name, description, id from forensics.crime_motive order by name asc;";
}

QString CrimeMotiveGateway::loadByIdQueryText() const
{
    return "select name, description, id from forensics.crime_motive where id = :id;";
}

void CrimeMotiveGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
