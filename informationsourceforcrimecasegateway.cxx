#include "informationsourceforcrimecasegateway.hxx"

#include "informationsourcetype.hxx"
#include "datacollector.hxx"
#include "crimecase.hxx"

void InformationSourceForCrimeCaseGateway::loadAllInCrimeCase(CrimeCaseSPtr c)
{
    auto q = DataCollector::get()->prepareQuery("select "
                                                "id, information_source_type_id, crime_case_id, url, when_added, description "
                                                "from forensics.information_source_for_crime_case "
                                                " where crime_case_id = :crime_case_id;");
    q.bindValue(":crime_case_id", c->id());

    DataCollector::get()->performQuery(q, false);

    while(q.next()) {
        auto rec = q.record();
        auto s = std::make_shared<InformationSourceForCrimeCase>();
        s->setCrimeCase(c);
        parse(s, rec);
        c->addInformationSource(s);
    }
}

void InformationSourceForCrimeCaseGateway::remove(int id)
{
    auto q = DataCollector::get()->prepareQuery("delete from forensics.information_source_for_crime_case where id = :id;");
    q.bindValue(":id", id);
    DataCollector::get()->performQuery(q, true);
}

QString InformationSourceForCrimeCaseGateway::loadAllQueryText() const
{
    return "select "
           "id, information_source_type_id, crime_case_id, url, when_added, description "
           "from forensics.information_source_for_crime_case "
           "order by crime_case_id, information_source_type_id, crime_case_id, when_added;";
}

QString InformationSourceForCrimeCaseGateway::loadByIdQueryText() const
{
    return "select "
           "id, information_source_type_id, crime_case_id, url, when_added, description "
           "from forensics.information_source_for_crime_case "
           " where id = :id;";
}

void InformationSourceForCrimeCaseGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setUrl(rec.value(rec.indexOf("url")).toString());
    t->informationSourceType()->setId(rec.value(rec.indexOf("url")).toInt());
    t->setWhenAdded(rec.value(rec.indexOf("when_added")).toDateTime());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
