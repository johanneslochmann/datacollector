#include "weapongateway.hxx"

QString WeaponGateway::loadAllQueryText() const
{
    return "select name, description, id from forensics.weapon order by name asc;";
}

QString WeaponGateway::loadByIdQueryText() const
{
    return "select name, description, id from forensics.weapon where id = :id;";
}

void WeaponGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
