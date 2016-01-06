#include "crimecaseparticipantgateway.hxx"

#include <QDebug>

#include "datacollector.hxx"

#include "crimecase.hxx"
#include "crimecaseparticipant.hxx"
#include "crimecasepartyrolegateway.hxx"
#include "sexdatagateway.hxx"
#include "crimetypegateway.hxx"
#include "jobgateway.hxx"
#include "crimemotivegateway.hxx"
#include "mentaldiseasegateway.hxx"
#include "modusoperandigateway.hxx"
#include "weapongateway.hxx"
#include "consultancyresultgateway.hxx"

void CrimeCaseParticipantGateway::loadAllInCrimeCase(CrimeCaseSPtr crimeCase)
{
    auto q = DataCollector::get()->prepareQuery("select "
                                                "id, crime_case_party_role_id, crime_case_id, sex_id, "
                                                "age_in_years, has_precedent_convictions, crime_type_id, "
                                                "modus_operandi_id, mental_disease_id, crime_motive_id, consultancy_result_id, "
                                                "weapon_id, description, name, job_id, has_precedent_convictions, "
                                                "is_drug_intoxicated, is_alcohol_intoxicated "
                                                "from forensics.crime_case_participant "
                                                "where crime_case_id = :case_id;");
    q.bindValue(":case_id", crimeCase->id());

    DataCollector::get()->performQuery(q, false);

    CrimeCaseParticipantSPtrVector buf;

    while(q.next()) {
        auto c = std::make_shared<CrimeCaseParticipant>();
        parse(c, q.record());
        loadSubRecords(c);
        buf.push_back(c);
    }

    crimeCase->setParticipants(buf);
}

void CrimeCaseParticipantGateway::remove(int id)
{
    auto q = DataCollector::get()->prepareQuery("delete from forensics.crime_case_participant where id = :id;");
    q.bindValue(":id", id);
    DataCollector::get()->performQuery(q, true);
}

void CrimeCaseParticipantGateway::save(CrimeCaseParticipantSPtr c)
{
    if (c->id() > 0) {
        update(c);
    } else {
        insert(c);
    }
}

QString CrimeCaseParticipantGateway::loadAllQueryText() const
{
    return "select "
           "id, crime_case_party_role_id, crime_case_id, sex_id, "
           "age_in_years, has_precedent_convictions, crime_type_id, "
           "modus_operandi_id, mental_disease_id, crime_motive_id, consultancy_result_id, "
           "weapon_id, description, name, job_id, has_precedent_convictions, "
           "is_drug_intoxicated, is_alcohol_intoxicated "
           "from forensics.crime_case_participant "
           "order by id;";
}

QString CrimeCaseParticipantGateway::loadByIdQueryText() const
{
    return "select "
           "id, crime_case_party_role_id, crime_case_id, sex_id, "
           "age_in_years, has_precedent_convictions, crime_type_id, "
           "modus_operandi_id, mental_disease_id, crime_motive_id, consultancy_result_id, "
           "weapon_id, description, name, job_id, has_precedent_convictions, "
           "is_drug_intoxicated, is_alcohol_intoxicated "
           "from forensics.crime_case_participant "
           "where id = :id;";
}

void CrimeCaseParticipantGateway::parse(std::shared_ptr<DataGateway::DataType> t, const QSqlRecord &rec)
{
    t->setId(rec.value(rec.indexOf("id")).toInt());
    t->setName(rec.value(rec.indexOf("name")).toString());
    t->setDescription(rec.value(rec.indexOf("description")).toString());
    t->setAgeInYears(rec.value(rec.indexOf("age_in_years")).toInt());
    t->crimeCase()->setId(rec.value(rec.indexOf("crime_case_id")).toInt());
    t->role()->setId(rec.value(rec.indexOf("crime_case_party_role_id")).toInt());
    t->sex()->setId(rec.value(rec.indexOf("sex_id")).toInt());
    t->crimeType()->setId(rec.value(rec.indexOf("crime_type_id")).toInt());
    t->job()->setId(rec.value(rec.indexOf("job_id")).toInt());
    t->motive()->setId(rec.value(rec.indexOf("crime_motive_id")).toInt());
    t->mentalDisease()->setId(rec.value(rec.indexOf("mental_disease_id")).toInt());
    t->modusOperandi()->setId(rec.value(rec.indexOf("modus_operandi_id")).toInt());
    t->weapon()->setId(rec.value(rec.indexOf("weapon_id")).toInt());
    t->consultancyResult()->setId(rec.value(rec.indexOf("consultancy_result_id")).toInt());
    t->setHasPrecedentConvictions(rec.value(rec.indexOf("has_precedent_convictions")).toBool());    
    t->setIsAlcoholIntoxicated(rec.value(rec.indexOf("is_alcohol_intoxicated")).toBool());
    t->setIsDrugIntoxicated(rec.value(rec.indexOf("is_drug_intoxicated")).toBool());
}

void CrimeCaseParticipantGateway::insert(CrimeCaseParticipantSPtr c)
{
    auto q = DataCollector::get()->prepareQuery("insert into forensics.crime_case_participant "
                                                "(crime_case_id, name, age_in_years, description, crime_case_party_role_id, "
                                                "sex_id, crime_type_id, job_id, crime_motive_id, mental_disease_id, "
                                                "modus_operandi_id, weapon_id, has_precedent_convictions, "
                                                "is_alcohol_intoxicated, is_drug_intoxicated) values "
                                                "(:crime_case_id, :name, :age_in_years, :description, :crime_case_party_role_id, "
                                                ":sex_id, :crime_type_id, :job_id, :crime_motive_id, :mental_disease_id, "
                                                ":modus_operandi_id, :weapon_id, :has_precedent_convictions, "
                                                ":is_alcohol_intoxicated, :is_drug_intoxicated) "
                                                "returning id;");
    q.bindValue(":crime_case_id", c->crimeCase()->id());
    q.bindValue(":name", c->name());
    q.bindValue(":age_in_years", c->ageInYears() > 0 ? c->ageInYears() : QVariant(QVariant::Int));
    q.bindValue(":description", c->description());
    q.bindValue(":crime_case_party_role_id", (c->role() && c->role()->id()) > 0 ? c->role()->id() : QVariant(QVariant::Int));
    q.bindValue(":sex_id", (c->sex() && c->sex()->id()) > 0 ? c->sex()->id() : QVariant(QVariant::Int));
    q.bindValue(":crime_type_id", (c->crimeType() && c->crimeType()->id()) > 0 ? c->crimeType()->id() : QVariant(QVariant::Int));
    q.bindValue(":job_id", (c->job() && c->job()->id()) > 0 ? c->job()->id() : QVariant(QVariant::Int));
    q.bindValue(":crime_motive_id", (c->motive() && c->motive()->id()) > 0 ? c->motive()->id() : QVariant(QVariant::Int));
    q.bindValue(":mental_disease_id", (c->mentalDisease() && c->mentalDisease()->id()) > 0 ? c->mentalDisease()->id() : QVariant(QVariant::Int));
    q.bindValue(":modus_operandi_id", (c->modusOperandi() && c->modusOperandi()->id()) > 0 ? c->modusOperandi()->id() : QVariant(QVariant::Int));
    q.bindValue(":weapon_id", (c->weapon() && c->weapon()->id()) > 0 ? c->weapon()->id() : QVariant(QVariant::Int));
    q.bindValue(":consultancy_result_id", (c->consultancyResult() && c->consultancyResult()->id()) > 0 ? c->consultancyResult()->id() : QVariant(QVariant::Int));
    q.bindValue(":has_precedent_convictions", c->hasPrecedentConvictions());
    q.bindValue(":is_alcohol_intoxicated", c->isAlcoholIntoxicated());
    q.bindValue(":is_drug_intoxicated", c->isDrugIntoxicated());

    DataCollector::get()->performQueryWithExpectedSize(q, 1, true);
    q.next();
    c->setId(q.record().value("id").toInt());
}

void CrimeCaseParticipantGateway::update(CrimeCaseParticipantSPtr c)
{
    auto q = DataCollector::get()->prepareQuery("update forensics.crime_case_participant "
                                                "set "
                                                "crime_case_id = :crime_case_id, "
                                                "name = :name, "
                                                "age_in_years = :age_in_years, "
                                                "description = :description, "
                                                "crime_case_party_role_id = :crime_case_party_role_id, "
                                                "sex_id = :sex_id, "
                                                "crime_type_id = :crime_type_id, "
                                                "job_id = :job_id, "
                                                "crime_motive_id = :crime_motive_id, "
                                                "mental_disease_id = :mental_disease_id, "
                                                "modus_operandi_id = :modus_operandi_id, "
                                                "weapon_id = :weapon_id, "
                                                "consultancy_result_id = :consultancy_result_id, "
                                                "has_precedent_convictions = :has_precedent_convictions, "
                                                "is_alcohol_intoxicated = :is_alcohol_intoxicated, "
                                                "is_drug_intoxicated = :is_drug_intoxicated, "
                                                "where id = :id;");

    q.bindValue(":id", c->id());
    q.bindValue(":crime_case_id", c->crimeCase()->id());
    q.bindValue(":name", c->name());
    q.bindValue(":age_in_years", c->ageInYears() > 0 ? c->ageInYears() : QVariant(QVariant::Int));
    q.bindValue(":description", c->description());
    q.bindValue(":crime_case_party_role_id", (c->role() && c->role()->id()) > 0 ? c->role()->id() : QVariant(QVariant::Int));
    q.bindValue(":sex_id", (c->sex() && c->sex()->id()) > 0 ? c->sex()->id() : QVariant(QVariant::Int));
    q.bindValue(":crime_type_id", (c->crimeType() && c->crimeType()->id()) > 0 ? c->crimeType()->id() : QVariant(QVariant::Int));
    q.bindValue(":job_id", (c->job() && c->job()->id()) > 0 ? c->job()->id() : QVariant(QVariant::Int));
    q.bindValue(":crime_motive_id", (c->motive() && c->motive()->id()) > 0 ? c->motive()->id() : QVariant(QVariant::Int));
    q.bindValue(":mental_disease_id", (c->mentalDisease() && c->mentalDisease()->id()) > 0 ? c->mentalDisease()->id() : QVariant(QVariant::Int));
    q.bindValue(":modus_operandi_id", (c->modusOperandi() && c->modusOperandi()->id()) > 0 ? c->modusOperandi()->id() : QVariant(QVariant::Int));
    q.bindValue(":weapon_id", (c->weapon() && c->weapon()->id()) > 0 ? c->weapon()->id() : QVariant(QVariant::Int));
    q.bindValue(":consultancy_result_id", (c->consultancyResult() && c->consultancyResult()->id()) > 0 ? c->consultancyResult()->id() : QVariant(QVariant::Int));
    q.bindValue(":has_precedent_convictions", c->hasPrecedentConvictions());
    q.bindValue(":is_alcohol_intoxicated", c->isAlcoholIntoxicated());
    q.bindValue(":is_drug_intoxicated", c->isDrugIntoxicated());

    DataCollector::get()->performQuery(q, true);
}

void CrimeCaseParticipantGateway::loadSubRecords(CrimeCaseParticipantSPtr c)
{
    if (c->role()->id() > 0) {
        c->setRole(CrimeCasePartyRoleGateway().loadById(c->role()->id()));
    }

    if (c->sex()->id() > 0) {
        c->setSex(SexDataGateway().loadById(c->sex()->id()));
    }

    if (c->crimeType()->id() > 0) {
        c->setCrimeType(CrimeTypeGateway().loadById(c->crimeType()->id()));
    }

    if (c->job()->id() > 0) {
        c->setJob(JobGateway().loadById(c->job()->id()));
    }

    if (c->motive()->id() > 0) {
        c->setMotive(CrimeMotiveGateway().loadById(c->motive()->id()));
    }

    if (c->mentalDisease()->id() > 0) {
        c->setMentalDisease(MentalDiseaseGateway().loadById(c->mentalDisease()->id()));
    }

    if (c->modusOperandi()->id() > 0) {
        c->setModusOperandi(ModusOperandiGateway().loadById(c->modusOperandi()->id()));
    }

    if (c->weapon()->id() > 0) {
        c->setWeapon(WeaponGateway().loadById(c->weapon()->id()));
    }

    if (c->consultancyResult()->id() > 0) {
        c->setConsultancyResult(ConsultancyResultGateway().loadById(c->consultancyResult()->id()));
    }
}

CrimeCaseParticipantGateway::CrimeCaseParticipantGateway()
    : DataGateway<CrimeCaseParticipant>()
{
}
