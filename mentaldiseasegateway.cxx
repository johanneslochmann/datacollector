#include "mentaldiseasegateway.hxx"

QString MentalDiseaseGateway::loadAllQueryText() const
{
    return "select name, description, id from forensics.mental_disease order by name asc;";
}

QString MentalDiseaseGateway::loadByIdQueryText() const
{
    return "select name, description, id from forensics.mental_disease where id = :id;";
}

void MentalDiseaseGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}
