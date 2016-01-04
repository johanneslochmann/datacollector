#include "informationsourceforcrimecasegateway.hxx"

#include "informationsourcetype.hxx"
#include "datacollector.hxx"
#include "crimecase.hxx"

#include "informationsourcetypegateway.hxx"

void InformationSourceForCrimeCaseGateway::loadAllInCrimeCase(CrimeCaseSPtr c)
{
    auto q = DataCollector::get()->prepareQuery("select "
                                                "id, information_source_type_id, crime_case_id, url, when_added, description "
                                                "from forensics.information_source_for_crime_case "
                                                "where crime_case_id = :crime_case_id;");
    q.bindValue(":crime_case_id", c->id());

    DataCollector::get()->performQuery(q, false);

    InformationSourceForCrimeCaseSPtrVector buf;

    while(q.next()) {
        auto rec = q.record();
        auto s = std::make_shared<InformationSourceForCrimeCase>();
        parse(s, rec);
        s->setCrimeCase(c);
        s->setInformationSourceType(InformationSourceTypeGateway().loadById(s->informationSourceType()->id()));

        buf.push_back(s);
    }

    c->setInformationSources(buf);
}

void InformationSourceForCrimeCaseGateway::remove(int id)
{
    auto q = DataCollector::get()->prepareQuery("delete from forensics.information_source_for_crime_case where id = :id;");
    q.bindValue(":id", id);
    DataCollector::get()->performQuery(q, true);
}

void InformationSourceForCrimeCaseGateway::save(InformationSourceForCrimeCaseSPtr d)
{
    if (d->id() > 0) {
        update(d);
    } else {
        insert(d);
    }
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
    t->informationSourceType()->setId(rec.value(rec.indexOf("information_source_type_id")).toInt());
    t->setWhenAdded(rec.value(rec.indexOf("when_added")).toDateTime());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}

void InformationSourceForCrimeCaseGateway::insert(InformationSourceForCrimeCaseSPtr d)
{
    auto q = DataCollector::get()->prepareQuery("insert into forensics.information_source_for_crime_case "
                                                "(information_source_type_id, crime_case_id, url, when_added, description) values "
                                                "(:information_source_type_id, :crime_case_id, :url, :when_added, :description) "
                                                "returning id;");

    q.bindValue(":information_source_type_id", d->informationSourceType()->id());
    q.bindValue(":crime_case_id", d->crimeCase()->id());
    q.bindValue(":url", d->url());
    q.bindValue(":when_added", d->whenAdded());
    q.bindValue(":description", d->description());

    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
    q.next();
    d->setId(q.record().value("id").toInt());
}

void InformationSourceForCrimeCaseGateway::update(InformationSourceForCrimeCaseSPtr d)
{
    auto q = DataCollector::get()->prepareQuery("update forensics.information_source_for_crime_case set "
                                                "information_source_type_id = :information_source_type_id, "
                                                "crime_case_id = :crime_case_id, "
                                                "url = :url, "
                                                "when_added = :when_added, "
                                                "description = :description "
                                                "where id = :id "
                                                "returning id;");

    q.bindValue(":information_source_type_id", d->informationSourceType()->id());
    q.bindValue(":crime_case_id", d->crimeCase()->id());
    q.bindValue(":url", d->url());
    q.bindValue(":when_added", d->whenAdded());
    q.bindValue(":description", d->description());
    q.bindValue(":id", d->id());

    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
}
