#include "modusoperandigateway.hxx"

QString ModusOperandiGateway::loadAllQueryText() const
{
    return "select name, description, id from forensics.modus_operandi order by name asc;";
}

QString ModusOperandiGateway::loadByIdQueryText() const
{
    return "select name, description, id from forensics.modus_operandi where id = :id;";
}

void ModusOperandiGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
