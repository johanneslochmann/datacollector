#include "campaigndatagateway.hxx"

#include "datacollector.hxx"

CampaignSPtrVector CampaignDataGateway::campaignsInProject(int projectId)
{
    auto q = DataCollector::get()->prepareQuery("select "
                                                "c.id, c.name, c.start_date, c.end_date, c.description, "
                                                " p.name as project_name, p.id as project_id "
                                                "from core.campaign c "
                                                "join core.project p on c.project_id = p.id "
                                                "where c.project_id = :project_id "
                                                "order by c.name asc;");
    q.bindValue(":project_id", projectId);

    DataCollector::get()->performQuery(q);

    CampaignSPtrVector buf;

    while(q.next()) {
        auto c = std::make_shared<Campaign>();
        parse(c, q.record());
        buf.push_back(c);
    }

    return buf;
}

QString CampaignDataGateway::loadAllQueryText() const
{
    return "select "
           "c.id, c.name, c.start_date, c.end_date, c.description, "
           " p.name as project_name, p.id as project_id "
           "from core.campaign c "
           "join core.project p on c.project_id = p.id "
           "order by c.name asc;";
}

void CampaignDataGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setBegin(rec.value(rec.indexOf("start_date")).toDate());
    t->setEnd(rec.value(rec.indexOf("end_date")).toDate());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
    t->setProjectId(rec.value(rec.indexOf("project_id")).toInt());
    t->setProjectName(rec.value(rec.indexOf("project_name")).toString());
}
