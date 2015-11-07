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

void SurveyGateway::addIcd10DiagnosisToSurvey(int icd10DiagnosisId, const QString &comment, int surveyId)
{
    auto q = DataCollector::get()->prepareQuery("insert into core.icd10_survey(icd10_diagnosis_id, survey_id, description) "
                                                "values (:icd10_diagnosis_id, :survey_id, :comment) "
                                                "returning id;");
    q.bindValue(":icd10_diagnosis_id", icd10DiagnosisId);
    q.bindValue(":survey_id", surveyId);
    q.bindValue(":comment", comment);
    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
}

void SurveyGateway::addCollateralEffectToSurvey(int effectId, const QString &comment, int surveyId)
{
    auto q = DataCollector::get()->prepareQuery("insert into core.survey_collateral_effect(collateral_effect_id, survey_id, description) "
                                                "values (:collateral_effect_id, :survey_id, :comment) "
                                                "returning id;");
    q.bindValue(":collateral_effect_id", effectId);
    q.bindValue(":survey_id", surveyId);
    q.bindValue(":comment", comment);
    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
}

void SurveyGateway::addOnDemandDrugToSurvey(int drugId, const QString& description, int surveyId)
{

    auto q = DataCollector::get()->prepareQuery("insert into core.optional_prescription(drug_id, survey_id, description) "
                                                "values (:drug_id, :survey_id, :comment) "
                                                "returning id;");
    q.bindValue(":drug_id", drugId);
    q.bindValue(":survey_id", surveyId);
    q.bindValue(":comment", description);
    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
}

void SurveyGateway::addRegularDrugToSurvey(int prescribeableDrugId, double morning, double lunch, double noon, double night, const QString& description, int surveyId)
{
    auto q = DataCollector::get()->prepareQuery("insert into "
                                                "core.regular_prescription(prescribeable_drug_id, survey_id, morning_dosage, lunch_dosage, noon_dosage, night_dosage, description) "
                                                "values (:prescribable_drug_id, :survey_id, :morning, :lunch, :noon, :night, :description) "
                                                "returning id;");
    q.bindValue(":prescribable_drug_id", prescribeableDrugId);    
    q.bindValue(":survey_id", surveyId);
    q.bindValue(":morning", morning);
    q.bindValue(":lunch", lunch);
    q.bindValue(":noon", noon);
    q.bindValue(":night", night);
    q.bindValue(":description", description);
    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
}

void SurveyGateway::addPlasmaticLevelToSurvey(int moleculeId, double value, const QString &unitName, const QString& comment, int surveyId)
{
    auto q = DataCollector::get()->prepareQuery("insert into "
                                                "core.plasmatic_level(molecule_id, concentration_value, unit_id, survey_id, description) "
                                                "values (:molecule_id, :value, (select id from core.unit where name = :unit_name), :survey_id, :description) "
                                                "returning id;");
    q.bindValue(":molecule_id", moleculeId);
    q.bindValue(":value", value);
    q.bindValue(":unit_name", unitName);
    q.bindValue(":survey_id", surveyId);
    q.bindValue(":description", comment);
    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
}

void SurveyGateway::addDepotDrugToSurvey(int prescribeableDrugId, double dosage, const QDate &lastInjection, int interval, const QString& comment, int surveyId)
{
    auto q = DataCollector::get()->prepareQuery("insert into "
                                                "core.depot_prescription(prescribeable_drug_id, dosage, last_injection_on, injection_interval_in_days, survey_id, description) "
                                                "values (:drug_id, :dosage, :last_injection, :interval, :survey_id, :description) "
                                                "returning id;");
    q.bindValue(":drug_id", prescribeableDrugId);
    q.bindValue(":dosage", dosage);
    q.bindValue(":last_injection", lastInjection);
    q.bindValue(":interval", interval);
    q.bindValue(":survey_id", surveyId);
    q.bindValue(":description", comment);

    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
}

void SurveyGateway::addCgiToSurvey(double severity, double improvement, const QString &description, int surveyId)
{
    auto q = DataCollector::get()->prepareQuery("insert into "
                                                "core.cgi(survey_id, severity, improvement, description) "
                                                "values(:survey_id, :severity, :improvement, :description) "
                                                "returning id;");
    q.bindValue(":survey_id", surveyId);
    q.bindValue(":description", description);
    q.bindValue(":severity", severity);
    q.bindValue(":improvement", improvement);

    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
}

void SurveyGateway::addGafToSurvey(double value, const QString &description, int surveyId)
{
    auto q = DataCollector::get()->prepareQuery("insert into "
                                                "core.gaf(survey_id, gaf_value, description) "
                                                "values(:survey_id, :value, :description) "
                                                "returning id;");
    q.bindValue(":survey_id", surveyId);
    q.bindValue(":description", description);
    q.bindValue(":value", value);

    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
}

void SurveyGateway::addFpsToSurvey(double value, const QString &description, int surveyId)
{
    auto q = DataCollector::get()->prepareQuery("insert into "
                                                "core.fps(survey_id, fps_value, description) "
                                                "values(:survey_id, :value, :description) "
                                                "returning id;");
    q.bindValue(":survey_id", surveyId);
    q.bindValue(":description", description);
    q.bindValue(":value", value);

    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
}

void SurveyGateway::addWhoQolToSurvey(double physical, double psychological, double social, double environmental, const QString &description, int surveyId)
{
    auto q = DataCollector::get()->prepareQuery("insert into "
                                                "core.who_qol(survey_id, physical, psychological, social, environmental, description) "
                                                "values(:survey_id, :physical, :psychological, :social, :environmental, :description) "
                                                "returning id;");
    q.bindValue(":survey_id", surveyId);
    q.bindValue(":description", description);
    q.bindValue(":physical", physical);
    q.bindValue(":psychological", psychological);
    q.bindValue(":social", social);
    q.bindValue(":environmental", environmental);

    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
}

void SurveyGateway::removeSurvey(int id)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.survey where id = :id;");

    q.bindValue(":id", id);

    DataCollector::get()->performQuery(q, true);
}

void SurveyGateway::removeIcd10DiagnosisFromSurvey(int recordId)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.icd10_survey where id = :id;");

    q.bindValue(":id", recordId);

    DataCollector::get()->performQuery(q, true);
}

void SurveyGateway::removeCollateralEffectFromSurvey(int recordId)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.survey_collateral_effect where id = :id;");

    q.bindValue(":id", recordId);

    DataCollector::get()->performQuery(q, true);
}

void SurveyGateway::removeOnDemandDrugFromSurvey(int recordId)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.optional_prescription where id = :id;");

    q.bindValue(":id", recordId);

    DataCollector::get()->performQuery(q, true);
}

void SurveyGateway::removeRegularDrugFromSurvey(int recordId)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.regular_prescription where id = :id;");

    q.bindValue(":id", recordId);

    DataCollector::get()->performQuery(q, true);
}

void SurveyGateway::removePlasmaticLevelFromSurvey(int recordId)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.plasmatic_level where id = :id;");

    q.bindValue(":id", recordId);

    DataCollector::get()->performQuery(q, true);
}

void SurveyGateway::removeDepotDrugFromSurvey(int recordId)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.depot_prescription where id = :id;");

    q.bindValue(":id", recordId);

    DataCollector::get()->performQuery(q, true);
}

void SurveyGateway::removeCgiFromSurvey(int recordId)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.cgi where id = :id;");

    q.bindValue(":id", recordId);

    DataCollector::get()->performQuery(q, true);
}

void SurveyGateway::removeGafFromSurvey(int recordId)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.gaf where id = :id;");

    q.bindValue(":id", recordId);

    DataCollector::get()->performQuery(q, true);
}

void SurveyGateway::removeFpsFromSurvey(int recordId)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.fps where id = :id;");

    q.bindValue(":id", recordId);

    DataCollector::get()->performQuery(q, true);
}

void SurveyGateway::removeWhoQolFromSurvey(int recordId)
{
    auto q = DataCollector::get()->prepareQuery("delete from core.who_qol where id = :id;");

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
    t->setBmi(rec.value(rec.indexOf("bmi")).toDouble());
}

void SurveyGateway::insert(SurveySPtr s)
{
    auto q = DataCollector::get()->prepareQuery("insert into "
                                                "core.survey(proband_id, campaign_id, organization_unit_id, survey_date, description, smoking_habit_id, bmi) "
                                                "values(:proband_id, :campaign_id, :organization_unit_id, :survey_date, :description, :smoking_habit_id, :bmi) "
                                                "returning id;");
    q.bindValue(":proband_id", s->probandId());
    q.bindValue(":campaign_id", s->campaignId());
    q.bindValue(":organization_unit_id", s->organizationUnitId());
    q.bindValue(":survey_date", s->date());
    q.bindValue(":description", s->description());
    q.bindValue(":smoking_habit_id", s->smokingHabitId());
    q.bindValue(":bmi", (s->bmi() > 0.0) ? s->bmi() : QVariant());

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
