#include "surveygateway.hxx"

#include "datacollector.hxx"

void SurveyGateway::save(SurveySPtr s)
{
    if (s->hasId()) {
        update(s);
    } else {
        insert(s);
    }
}

QString SurveyGateway::loadAllQueryText() const
{
    return "select proband_id, campaign_id, organization_unit_id, survey_date, id, description "
           "from core.survey "
           "order by campaign_id, organization_unit_id, proband_id, survey_date;";
}

void SurveyGateway::parse(SurveySPtr t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setProbandId(rec.value(rec.indexOf("proband_id")).toInt());
    t->setCampaignId(rec.value(rec.indexOf("campaign_id")).toInt());
    t->setOrganizationUnitId(rec.value(rec.indexOf("organization_unit_id")).toInt());
    t->setDate(rec.value(rec.indexOf("survey_date")).toDate());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
}

void SurveyGateway::insert(SurveySPtr s)
{
    auto q = DataCollector::get()->prepareQuery("insert into "
                                                "core.survey(proband_id, campaign_id, organization_unit_id, survey_date, description) "
                                                "values(:proband_id, :campaign_id, :organization_unit_id, :survey_date, :description) "
                                                "returning id;");
    q.bindValue(":proband_id", s->probandId());
    q.bindValue(":campaign_id", s->campaignId());
    q.bindValue(":organization_unit_id", s->organizationUnitId());
    q.bindValue(":survey_date", s->date());
    q.bindValue(":description", s->description());

    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);

    q.next();

    parse(s, q.record());
}

void SurveyGateway::update(SurveySPtr s)
{
    auto q = DataCollector::get()->prepareQuery("update core.survey set "
                                                "proband_id = :proband_id, "
                                                "campaign_id = :campaign_id, "
                                                "organization_unit_id = :organization_unit_id, "
                                                "survey_date = :survey_date, "
                                                "description = :description "
                                                "where id = :id");
    q.bindValue(":proband_id", s->probandId());
    q.bindValue(":campaign_id", s->campaignId());
    q.bindValue(":organization_unit_id", s->organizationUnitId());
    q.bindValue(":survey_date", s->date());
    q.bindValue(":description", s->description());
    q.bindValue(":id", s->id());

    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);

    q.next();

    parse(s, q.record());
}
