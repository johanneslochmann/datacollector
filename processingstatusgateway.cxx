#include "processingstatusgateway.hxx"

QString ProcessingStatusGateway::loadAllQueryText() const
{
    return "select name, description, id from core.processing_status order by name asc;";
}

QString ProcessingStatusGateway::loadByIdQueryText() const
{
    return "select name, description, id from core.processing_status where id = :id;";
}

void ProcessingStatusGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
