#include "crimecaseparticipantgateway.hxx"

#include "datacollector.hxx"

CrimeCaseParticipantSPtrVector CrimeCaseParticipantGateway::crimeCaseParticipantsInCrimeCase(int caseId)
{
    /*auto q = DataCollector::get()->prepareQuery("select "
                                                "c.id, c.name, c.start_date, c.end_date, c.description, "
                                                " p.name as project_name, p.id as project_id "
                                                "from core.CrimeCaseParticipant c "
                                                "join core.project p on c.project_id = p.id "
                                                "where c.project_id = :project_id "
                                                "order by c.name asc;");
    q.bindValue(":project_id", projectId);

    DataCollector::get()->performQuery(q, false);
*/
    CrimeCaseParticipantSPtrVector buf;

  /*  while(q.next()) {
        auto c = std::make_shared<CrimeCaseParticipant>();
        parse(c, q.record());
        buf.push_back(c);
    }
*/
    return buf;
}

QString CrimeCaseParticipantGateway::loadAllQueryText() const
{
    return "select "
           "c.id, c.name, c.start_date, c.end_date, c.description, "
           " p.name as project_name, p.id as project_id "
           "from core.CrimeCaseParticipant c "
           "join core.project p on c.project_id = p.id "
           "order by c.name asc;";
}

void CrimeCaseParticipantGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
}

CrimeCaseParticipantGateway::CrimeCaseParticipantGateway()
    : DataGateway<CrimeCaseParticipant>()
{}
