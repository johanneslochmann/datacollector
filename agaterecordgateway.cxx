#include "agaterecordgateway.hxx"

#include <QDebug>

#include "datacollector.hxx"

AgateRecordGateway::AgateRecordGateway()
{

}

void AgateRecordGateway::save(AgateRecordSPtr r)
{
    (void) r;
}

AgateRecordSPtrVector AgateRecordGateway::loadAllInProject(ProjectSPtr p)
{
    AgateRecordSPtrVector buf;

    auto q = DataCollector::get()->prepareQuery("select "
                                                "proj.name as project_name, "
                                                "proj.id as project_id, "
                                                "camp.name as campaign_name, "
                                                "camp.id as campaign_id, "
                                                "prob.id as proband_id, "
                                                "prob.first_name as proband_name, "
                                                "prob.surname as proband_surname, "
                                                "prob.external_id as proband_external_id, "
                                                "prob.birthday as proband_birthday, "
                                                "sex.name as proband_sex_name, "
                                                "sex.id as proband_sex_id, "
                                                "surv.id as survey_id, "
                                                "surv.survey_date as survey_date, "
                                                "org.name as organization_name, "
                                                "org.id as organization_id "
                                                "from core.project proj "
                                                "join core.campaign camp on proj.id = camp.project_id "
                                                "join core.survey surv on camp.id = surv.campaign_id "
                                                "join core.proband prob on surv.proband_id = prob.id "
                                                "join core.sex sex on prob.sex_id = sex.id "
                                                "join core.organization_unit org on surv.organization_unit_id = org.id "
                                                "where proj.id = :project_id "
                                                "order by campaign_name, proband_name, proband_surname, proband_external_id, proband_birthday, survey_id, survey_date;");
    q.bindValue(":project_id", p->id());

    DataCollector::get()->performQuery(q, false);

    while(q.next()) {
        auto rec = q.record();
        auto ar = std::make_shared<AgateRecord>();
        parse(ar, rec);
        buf.push_back(ar);
    }

    return buf;
}

AgateRecordSPtrVector AgateRecordGateway::loadAllInCampaign(CampaignSPtr c)
{
    AgateRecordSPtrVector buf;

    auto q = DataCollector::get()->prepareQuery("select "
                                                "proj.name as project_name, "
                                                "proj.id as project_id, "
                                                "camp.name as campaign_name, "
                                                "camp.id as campaign_id, "
                                                "prob.id as proband_id, "
                                                "prob.first_name as proband_name, "
                                                "prob.surname as proband_surname, "
                                                "prob.external_id as proband_external_id, "
                                                "prob.birthday as proband_birthday, "
                                                "sex.name as proband_sex_name, "
                                                "sex.id as proband_sex_id, "
                                                "surv.id as survey_id, "
                                                "surv.survey_date as survey_date, "
                                                "org.name as organization_name, "
                                                "org.id as organization_id "
                                                "from core.project proj "
                                                "join core.campaign camp on proj.id = camp.project_id "
                                                "join core.survey surv on camp.id = surv.campaign_id "
                                                "join core.proband prob on surv.proband_id = prob.id "
                                                "join core.sex sex on prob.sex_id = sex.id "
                                                "join core.organization_unit org on surv.organization_unit_id = org.id "
                                                "where camp.id = :campaign_id "
                                                "order by campaign_name, proband_name, proband_surname, proband_external_id, proband_birthday, survey_id, survey_date;");
    q.bindValue(":campaign_id", c->id());

    DataCollector::get()->performQuery(q, false);

    while(q.next()) {
        auto rec = q.record();
        auto ar = std::make_shared<AgateRecord>();
        parse(ar, rec);
        buf.push_back(ar);
    }

    return buf;
}

void AgateRecordGateway::parse(AgateRecordSPtr ar, const QSqlRecord &rec)
{
    ar->project()->setId(rec.value(rec.indexOf("project_id")).toInt());
    ar->project()->setName(rec.value(rec.indexOf("project_name")).toString());
    ar->campaign()->setId(rec.value(rec.indexOf("campaign_id")).toInt());
    ar->campaign()->setName(rec.value(rec.indexOf("campaign_name")).toString());
    ar->proband()->setId(rec.value(rec.indexOf("proband_id")).toInt());
    ar->proband()->setFirstName(rec.value(rec.indexOf("proband_name")).toString());
    ar->proband()->setSurname(rec.value(rec.indexOf("proband_surname")).toString());
    ar->proband()->setExternalId(rec.value(rec.indexOf("proband_external_id")).toString());
    ar->proband()->setBirthday(rec.value(rec.indexOf("proband_birthday")).toDate());
    ar->sex()->setName(rec.value(rec.indexOf("sex_name")).toString());
    ar->sex()->setId(rec.value(rec.indexOf("sex_id")).toInt());
    ar->survey()->setId(rec.value(rec.indexOf("survey_id")).toInt());
    ar->survey()->setDate(rec.value(rec.indexOf("survey_date")).toDate());
    ar->organization()->setName(rec.value(rec.indexOf("organization_name")).toString());
    ar->organization()->setId(rec.value(rec.indexOf("organization_id")).toInt());
}


