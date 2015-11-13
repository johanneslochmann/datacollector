#include "diagnosisgateway.hxx"

#include "datacollector.hxx"

DiagnosisGateway::DiagnosisGateway()
{

}

int DiagnosisGateway::loadIdFromName(const QString &name)
{
    auto q = DataCollector::get()->prepareQuery("select id from core.icd10_diagnosis where name = :name;");
    q.bindValue(":name", name);
    DataCollector::get()->performQueryWithExpectedSize(q, 1, false);
    q.next();
    return q.value(0).toInt();
}

