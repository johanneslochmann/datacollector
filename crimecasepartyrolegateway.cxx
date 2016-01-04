#include "crimecasepartyrolegateway.hxx"

QString CrimeCasePartyRoleGateway::loadAllQueryText() const
{
    return "select name, description, id from forensics.crime_case_party_role order by name asc;";
}

QString CrimeCasePartyRoleGateway::loadByIdQueryText() const
{
    return "select name, description, id from forensics.crime_case_party_role where id = :id;";
}

void CrimeCasePartyRoleGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
