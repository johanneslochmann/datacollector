#include "moleculegateway.hxx"

#include "datacollector.hxx"

MoleculeGateway::MoleculeGateway()
{

}

int MoleculeGateway::loadIdFromName(const QString &name)
{
    auto q = DataCollector::get()->prepareQuery("select id from core.molecule where name = :name;");
    q.bindValue(":name", name);
    DataCollector::get()->performQueryWithExpectedSize(q, 1, false);
    q.next();
    return q.value(0).toInt();
}

