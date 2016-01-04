#include "jobgateway.hxx"

QString JobGateway::loadAllQueryText() const
{
    return "select name, description, id from core.job order by name asc;";
}

QString JobGateway::loadByIdQueryText() const
{
    return "select name, description, id from core.job where id = :id;";
}

void JobGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
