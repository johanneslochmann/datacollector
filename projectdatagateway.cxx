#include "projectdatagateway.hxx"

#include <QSqlRecord>

QString ProjectDataGateway::loadAllQueryText() const
{
    return "select name, id from core.project order by name asc;";
}

void ProjectDataGateway::parse(std::shared_ptr<Project> t, const QSqlRecord& rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
}
