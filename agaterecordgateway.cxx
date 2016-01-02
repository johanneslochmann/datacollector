#include "agaterecordgateway.hxx"

#include <QDebug>

#include "datacollector.hxx"

AgateRecordGateway::AgateRecordGateway()
{

}

void AgateRecordGateway::save(AgateRecordSPtr r)
{
    try {
        DataCollector::get()->begin();
        createProband(r->proband());
        createSurvey(r);

        deleteDiagnosisFromSurvey(r);
        deleteDepotsFromSurvey(r);
        deleteRegularPrescriptionsFromSurvey(r);

        addDiagnosis(r);
        addDepots(r);
        addMoleculePrescriptions(r);

        DataCollector::get()->commit();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, QObject::tr("Failed to save AGATE record."));
        DataCollector::get()->rollback();
    }
}

void AgateRecordGateway::remove(int surveyId)
{
    try {
        DataCollector::get()->begin();
        auto qsurv = DataCollector::get()->prepareQuery("delete from core.survey where id = :survey_id;");
        auto qprob = DataCollector::get()->prepareQuery("delete from core.proband where id = (select proband_id from core.survey where id = :survey_id);");

        qsurv.bindValue(":survey_id", surveyId);
        qprob.bindValue(":survey_id", surveyId);

        DataCollector::get()->performQuery(qsurv, false);
        DataCollector::get()->performQuery(qprob, false);

        DataCollector::get()->commit();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, QObject::tr("Failed to delete AGATE record."));
        DataCollector::get()->rollback();
    }
}

AgateRecordSPtr AgateRecordGateway::loadById(int id)
{
    auto q = DataCollector::get()->prepareQuery("select "
                                                "proj.name as project_name, "
                                                "proj.id as project_id, "
                                                "camp.name as campaign_name, "
                                                "camp.id as campaign_id, "
                                                "prob.id as proband_id, "
                                                "prob.first_name as proband_name, "
                                                "prob.surname as proband_surname, "
                                                "prob.external_id as proband_external_id, "
                                                "prob.year_of_birth as proband_year_of_birth, "
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
                                                "where surv.id = :survey_id;");
    q.bindValue(":survey_id", id);

    DataCollector::get()->performQueryWithExpectedSize(q, 1, false);
    q.next();

    auto rec = q.record();
    auto ar = std::make_shared<AgateRecord>();
    parse(ar, rec);

    loadDetails(ar);

    return ar;
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
                                                "prob.year_of_birth as proband_year_of_birth, "
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
                                                "order by campaign_name, proband_name, proband_surname, proband_external_id, proband_year_of_birth, survey_id, survey_date;");
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
                                                "prob.year_of_birth as proband_year_of_birth, "
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
                                                "order by campaign_name, proband_name, proband_surname, proband_external_id, proband_year_of_birth, survey_id, survey_date;");
    q.bindValue(":campaign_id", c->id());

    DataCollector::get()->performQuery(q, false);

    while(q.next()) {
        auto rec = q.record();
        auto ar = std::make_shared<AgateRecord>();
        parse(ar, rec);
        loadDetails(ar);
        buf.push_back(ar);
    }

    return buf;
}

void AgateRecordGateway::loadDetails(AgateRecordSPtr r)
{
    loadDiagnosis(r);
    loadDepots(r);
    loadMoleculePrescriptions(r);
}

void AgateRecordGateway::loadDiagnosis(AgateRecordSPtr r)
{
    auto q = DataCollector::get()->prepareQuery("select d.id, d.name "
                                                "from core.icd10_diagnosis d "
                                                "join core.icd10_survey nm on nm.icd10_diagnosis_id = d.id "
                                                "where nm.survey_id = :survey_id "
                                                "order by d.name asc;");
    q.bindValue(":survey_id", r->survey()->id());
    DataCollector::get()->performQuery(q, false);

    while(q.next()) {
        auto rec = q.record();

        auto buf = std::make_shared<AgateDiagnosis>();
        buf->id = rec.value("id").toInt();
        buf->name = rec.value("name").toString();

        r->addDiagnosis(buf);
    }
}

void AgateRecordGateway::loadDepots(AgateRecordSPtr r)
{
    auto q = DataCollector::get()->prepareQuery("select "
                                                "pd.name as prescribeable_drug_name, "
                                                "p.last_injection_on, "
                                                "p.dosage, "
                                                "p.injection_interval_in_days, "
                                                "pd.id as prescribeable_drug_id "
                                                "from core.depot_prescription p "
                                                "join core.prescribeable_drug pd on p.prescribeable_drug_id = pd.id "
                                                "where survey_id = :survey_id "
                                                "order by 1, 2;");

    q.bindValue(":survey_id", r->survey()->id());
    DataCollector::get()->performQuery(q, false);

    while(q.next()) {
        auto rec = q.record();

        auto buf = std::make_shared<AgateDepot>();
        buf->prescribeableDrugName = rec.value("prescribeable_drug_name").toString();
        buf->prescribeableDrugId = rec.value("prescribeable_drug_id").toInt();
        buf->lastInjectionDate = rec.value("last_injection_on").toDate();
        buf->dosageInMg = rec.value("dosage").toDouble();
        buf->injectionIntervalInDays = rec.value("injection_interval_in_days").toInt();

        r->addDepot(buf);
    }
}

void AgateRecordGateway::loadMoleculePrescriptions(AgateRecordSPtr r)
{
    auto q = DataCollector::get()->prepareQuery("select "
                                                "m.id as molecule_id, "
                                                "m.name as molecule_name, "
                                                "p.dosage_in_mg as dosage_in_mg "
                                                "from core.molecule_prescription p "
                                                "join core.molecule m on m.id = p.molecule_id "
                                                "where p.survey_id = :survey_id;");

    q.bindValue(":survey_id", r->survey()->id());
    DataCollector::get()->performQuery(q, false);

    while(q.next()) {
        auto rec = q.record();

        auto buf = std::make_shared<AgateMedication>();
        buf->moleculeId = rec.value("molecule_id").toInt();
        buf->moleculeName = rec.value("molecule_name").toString();
        buf->dosageInMg = rec.value("dosage_in_mg").toDouble();

        r->addMedication(buf);
    }

}

void AgateRecordGateway::createProband(ProbandSPtr p)
{
    auto q = DataCollector::get()->prepareQuery("insert into core.proband(year_of_birth, sex_id) values (:yob, :sex_id) returning id;");
    q.bindValue(":yob", p->yearOfBirth());
    q.bindValue(":sex_id", p->sexId());

    DataCollector::get()->performQueryWithExpectedSize(q, 1, false);
    q.next();
    p->setId(q.value("id").toInt());
}

void AgateRecordGateway::createSurvey(AgateRecordSPtr r)
{
    auto q = DataCollector::get()->prepareQuery("insert into core.survey(campaign_id, survey_date, proband_id, organization_unit_id) values (:campaign_id, :survey_date, :proband_id, :organization_unit_id) returning id;");
    q.bindValue(":campaign_id", r->campaign()->id());
    q.bindValue(":proband_id", r->proband()->id());
    q.bindValue(":survey_date", r->survey()->date());
    q.bindValue(":organization_unit_id", r->organization()->id());

    DataCollector::get()->performQueryWithExpectedSize(q, 1, false);
    q.next();
    r->survey()->setId(q.value("id").toInt());
}

void AgateRecordGateway::deleteDiagnosisFromSurvey(AgateRecordSPtr r)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.icd10_survey where survey_id = :survey_id;");
    q.bindValue(":survey_id", r->survey()->id());
    DataCollector::get()->performQuery(q, false);
}

void AgateRecordGateway::deleteDepotsFromSurvey(AgateRecordSPtr r)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.depot_prescription where survey_id = :survey_id;");
    q.bindValue(":survey_id", r->survey()->id());
    DataCollector::get()->performQuery(q, false);
}

void AgateRecordGateway::deleteRegularPrescriptionsFromSurvey(AgateRecordSPtr r)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.regular_prescription where survey_id = :survey_id;");
    q.bindValue(":survey_id", r->survey()->id());
    DataCollector::get()->performQuery(q, false);
}

void AgateRecordGateway::addDiagnosis(AgateRecordSPtr r)
{
    auto q = DataCollector::get()->prepareQuery("insert into core.icd10_survey(survey_id, icd10_diagnosis_id) values (:survey_id, :diagnosis_id);");

    for (auto i : r->diagnosis()) {
        q.bindValue(":survey_id", r->survey()->id());
        q.bindValue(":diagnosis_id", i->id);

        DataCollector::get()->performQuery(q, false);
    }
}

void AgateRecordGateway::addDepots(AgateRecordSPtr r)
{
    auto q = DataCollector::get()->prepareQuery("insert into core.depot_prescription("
                                                "survey_id, "
                                                "prescribeable_drug_id, "
                                                "last_injection_on, "
                                                "dosage, "
                                                "injection_interval_in_days) values ("
                                                ":survey_id, "
                                                ":prescribeable_drug_id, "
                                                ":last_injection_on, "
                                                ":dosage, "
                                                ":injection_interval_in_days);");

    for (auto i : r->depots()) {
        q.bindValue(":survey_id", r->survey()->id());
        q.bindValue(":prescribeable_drug_id", i->prescribeableDrugId);
        q.bindValue(":last_injection_on", i->lastInjectionDate);
        q.bindValue(":dosage", i->dosageInMg);
        q.bindValue(":injection_interval_in_days", i->injectionIntervalInDays);

        DataCollector::get()->performQuery(q, false);
    }
}

void AgateRecordGateway::addMoleculePrescriptions(AgateRecordSPtr r)
{
    auto q = DataCollector::get()->prepareQuery("insert into core.molecule_prescription(survey_id, molecule_id, dosage_in_mg) "
                                                "values (:survey_id, :molecule_id, :dosage) "
                                                "returning id;");

    for (auto p : r->medication()) {
        q.bindValue(":survey_id", r->survey()->id());
        q.bindValue(":molecule_id", p->moleculeId);
        q.bindValue(":dosage", p->dosageInMg);

        DataCollector::get()->performQuery(q, false);
    }

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
    ar->proband()->setYearOfBirth(rec.value(rec.indexOf("proband_year_of_birth")).toInt());
    ar->sex()->setName(rec.value(rec.indexOf("proband_sex_name")).toString());
    ar->sex()->setId(rec.value(rec.indexOf("proband_sex_id")).toInt());
    ar->survey()->setId(rec.value(rec.indexOf("survey_id")).toInt());
    ar->survey()->setDate(rec.value(rec.indexOf("survey_date")).toDate());
    ar->organization()->setName(rec.value(rec.indexOf("organization_name")).toString());
    ar->organization()->setId(rec.value(rec.indexOf("organization_id")).toInt());
}


