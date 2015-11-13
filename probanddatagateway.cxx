#include "probanddatagateway.hxx"

QString ProbandDataGateway::loadAllQueryText() const
{
    return "select p.id, p.external_id, p.birthday, p.height_in_cm, p.sex_id, p.description, p.first_name, p.surname, s.name as sex_name, year_of_birth "
            "from core.proband p "
            "join core.sex s on p.sex_id = s.id "
           "order by p.surname, p.first_name, p.external_id;";
}

void ProbandDataGateway::parse(ProbandSPtr t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setExternalId(rec.value(rec.indexOf("external_id")).toString());
    t->setBirthday(rec.value(rec.indexOf("birthday")).toDate());
    t->setHeightInCm(rec.value(rec.indexOf("height_in_cm")).toInt());
    t->setSexId(rec.value(rec.indexOf("sex_id")).toInt());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
    t->setFirstName(rec.value(rec.indexOf("first_name")).toString());
    t->setSurname(rec.value(rec.indexOf("surname")).toString());
    t->setSex(rec.value(rec.indexOf("sex_name")).toString());
    t->setYearOfBirth(rec.value(rec.indexOf("year_of_birth")).toInt());
}
