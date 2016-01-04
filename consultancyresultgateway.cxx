#include "consultancyresultgateway.hxx"

QString ConsultancyResultGateway::loadAllQueryText() const
{
    return "select name, description, id from forensics.consultancy_result order by name asc;";
}

QString ConsultancyResultGateway::loadByIdQueryText() const
{
    return "select name, description, id from forensics.consultancy_result where id = :id;";
}

void ConsultancyResultGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
