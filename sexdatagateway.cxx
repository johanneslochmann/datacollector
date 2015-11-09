#include "sexdatagateway.hxx"

#include <QSqlRecord>

QString SexDataGateway::loadAllQueryText() const
{
    return "select name, id from core.sex order by name asc;";
}

void SexDataGateway::parse(std::shared_ptr<Sex> t, const QSqlRecord& rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
}
