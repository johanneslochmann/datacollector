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

void SurveyGateway::addIcd10DiagnosisToSurvey(int icd10DiagnosisId, int surveyId)
{
    auto q = DataCollector::get()->prepareQuery("insert into core.icd10_survey(icd10_diagnosis_id, survey_id) "
                                                "values (:icd10_diagnosis_id, :survey_id) "
                                                "returning id;");
    q.bindValue(":icd10_diagnosis_id", icd10DiagnosisId);
    q.bindValue(":survey_id", surveyId);
    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
}

void SurveyGateway::removeIcd10DiagnosisFromSurvey(int recordId)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.icd10_survey where id = :id;");

    q.bindValue(":id", recordId);

    DataCollector::get()->performQuery(q, true);
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
