#include "smokinghabitgateway.hxx"

QString SmokingHabitGateway::loadAllQueryText() const
{
    return "select name, description, max_cigarettes, id from core.smoking_habit order by name asc;";
}

void SmokingHabitGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
    t->setMaxCigarettes(rec.value(rec.indexOf("max_cigarettes")).toInt());
}
