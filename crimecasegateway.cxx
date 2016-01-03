#include "crimecasegateway.hxx"

#include "datacollector.hxx"

CrimeCaseGateway::CrimeCaseGateway()
{

}

bool CrimeCaseGateway::save(CrimeCaseSPtr c)
{
    try {
        DataCollector::get()->begin();

        if (c->hasId()) {
            update(c);
        } else {
            insert(c);
        }

        DataCollector::get()->commit();

        return true;
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, QObject::tr("Failed to save Crime Case record."));
        DataCollector::get()->rollback();
    }

    return false;
}

void CrimeCaseGateway::remove(int id)
{
    try {
        DataCollector::get()->begin();
        implDelete(id);
        DataCollector::get()->commit();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, QObject::tr("Failed to delete Crime Case record."));
        DataCollector::get()->rollback();
    }
}

CrimeCaseSPtrVector CrimeCaseGateway::loadAll()
{
    CrimeCaseSPtrVector buf;

    auto q = DataCollector::get()->prepareQuery("select id, name, city_id, housing_type_id, crime_year, crime_date, crime_time, description "
                                                "from forensics.crime_case "
                                                "order by name asc;");
    DataCollector::get()->performQuery(q, false);

    while(q.next()) {
        auto rec = q.record();
        auto c = std::make_shared<CrimeCase>();
        parse(c, rec);
        buf.push_back(c);
    }

    return buf;
}

CrimeCaseSPtr CrimeCaseGateway::loadById(int id)
{
    auto q = DataCollector::get()->prepareQuery("select id, name, city_id, housing_type_id, crime_year, crime_date, crime_time, description "
                                                "from forensics.crime_case "
                                                "where id = :id;");
    q.bindValue(":id", id);

    DataCollector::get()->performQueryWithExpectedSize(q, 1, false);

    q.next();

    auto rec = q.record();
    auto c = std::make_shared<CrimeCase>();
    parse(c, rec);

    return c;
}

void CrimeCaseGateway::insert(CrimeCaseSPtr c)
{
    auto q = DataCollector::get()->prepareQuery("insert into forensics.crime_case "
                                                "(name, city_id, housing_type_id, crime_year, crime_date, crime_time, description) "
                                                "values (:name, :city_id, :housing_type_id, :crime_year, :crime_date, :crime_time, :description) "
                                                "returning id;");
    q.bindValue(":name", c->name());
    q.bindValue(":city_id", (c->city()->id > 0) ? QVariant(c->city()->id) : QVariant(QVariant::Int));
    q.bindValue(":housing_type_id", (c->housingType()->id > 0) ? QVariant(c->housingType()->id) : QVariant(QVariant::Int));
    q.bindValue(":crime_year", c->crimeYear());
    q.bindValue(":crime_date", c->crimeDate());
    q.bindValue(":crime_time", c->crimeTime());
    q.bindValue(":description", c->description());

    DataCollector::get()->performQueryWithExpectedSize(q, 1, false);
    q.next();
    c->setId(q.value("id").toInt());
}

void CrimeCaseGateway::update(CrimeCaseSPtr c)
{
    auto q = DataCollector::get()->prepareQuery("update forensics.crime_case "
                                                "set "
                                                "name = :name, "
                                                "city_id = :city_id, "
                                                "housing_type_id = :housing_type_id, "
                                                "crime_year = :crime_year, "
                                                "crime_date = :crime_date, "
                                                "crime_time = :crime_time, "
                                                "description = :description "
                                                "where id = :id "
                                                "returning id;");

    q.bindValue(":name", c->name());
    q.bindValue(":city_id", (c->city()->id > 0) ? QVariant(c->city()->id) : QVariant(QVariant::Int));
    q.bindValue(":housing_type_id", (c->housingType()->id > 0) ? QVariant(c->housingType()->id) : QVariant(QVariant::Int));
    q.bindValue(":crime_year", c->crimeYear());
    q.bindValue(":crime_date", c->crimeDate());
    q.bindValue(":crime_time", c->crimeTime());
    q.bindValue(":description", c->description());
    q.bindValue(":id", c->id());

    DataCollector::get()->performQueryWithExpectedSize(q, 1, false);
}

void CrimeCaseGateway::implDelete(int id)
{
    auto q = DataCollector::get()->prepareQuery("delete from forensics.crime_case where id = :id");
    q.bindValue(":id", id);

    DataCollector::get()->performQuery(q, false);
}

void CrimeCaseGateway::parse(CrimeCaseSPtr c, const QSqlRecord &rec)
{
    c->setId(rec.value("id").toInt());
    c->setName(rec.value("name").toString());
    c->city()->id = rec.value("city_id").toInt();
    c->housingType()->id = rec.value("housing_type_id").toInt();
    c->setCrimeYear(rec.value("crime_year").toInt());
    c->setCrimeDate(QDate::fromString(rec.value("crime_date").toString(), Qt::ISODate));
    c->setCrimeTime(QTime::fromString(rec.value("crime_time").toString(), "hh:mm:ss"));
    c->setDescription(rec.value("description").toString());
}
