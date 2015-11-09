#include "prescribeabledruggateway.hxx"

#include "datacollector.hxx"

PrescribeableDrugGateway::PrescribeableDrugGateway()
{

}

int PrescribeableDrugGateway::loadIdFromName(const QString &name)
{
    auto q = DataCollector::get()->prepareQuery("select id from core.prescribeable_drug where name = :name;");
    q.bindValue(":name", name);
    DataCollector::get()->performQueryWithExpectedSize(q, 1, false);
    q.next();
    return q.value(0).toInt();
}

