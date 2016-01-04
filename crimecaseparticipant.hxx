#pragma once

#include "storable.hxx"

#include "crimecasepartyrole.hxx"
#include "sex.hxx"
#include "crimetype.hxx"
#include "job.hxx"
#include "crimemotive.hxx"
#include "mentaldisease.hxx"

class CrimeCase;

using CrimeCaseSPtr = std::shared_ptr<CrimeCase>;

class CrimeCaseParticipant;
using CrimeCaseParticipantSPtr = std::shared_ptr<CrimeCaseParticipant>;
using CrimeCaseParticipantSPtrVector = std::vector<CrimeCaseParticipantSPtr>;

class CrimeCaseParticipant : public Storable
{
public:
    CrimeCaseParticipant();

    CrimeCaseSPtr crimeCase() const;
    QString name() const;
    int ageInYears() const;
    QString description() const;
    CrimeCasePartyRoleSPtr role() const;
    SexSPtr sex() const;
    CrimeTypeSPtr crimeType() const;
    JobSPtr job() const;
    CrimeMotiveSPtr motive() const;
    MentalDiseaseSPtr mentalDisease() const;

    void setCrimeCase(const CrimeCaseSPtr &crimeCase);
    void setName(const QString &name);
    void setAgeInYears(int ageInYears);
    void setDescription(const QString &description);
    void setRole(const CrimeCasePartyRoleSPtr &role);
    void setSex(const SexSPtr &sex);
    void setCrimeType(const CrimeTypeSPtr &crimeType);
    void setJob(const JobSPtr &job);
    void setMotive(const CrimeMotiveSPtr &motive);
    void setMentalDisease(const MentalDiseaseSPtr &mentalDisease);

private:
    CrimeCaseSPtr m_crimeCase;

    QString m_name { "" };
    int m_ageInYears { 0 };
    QString m_description { "" };

    CrimeCasePartyRoleSPtr m_role { std::make_shared<CrimeCasePartyRole>() };
    SexSPtr m_sex { std::make_shared<Sex>() };
    CrimeTypeSPtr m_crimeType { std::make_shared<CrimeType>() };
    JobSPtr m_job { std::make_shared<Job>() };
    CrimeMotiveSPtr m_motive { std::make_shared<CrimeMotive>() };
    MentalDiseaseSPtr m_mentalDisease { std::make_shared<MentalDisease>() };
};

/*
CREATE TABLE forensics.crime_case_participant
(
  name      text
    id 				serial NOT NULL primary key,
  age_in_years			integer default null,
  description 			text NOT NULL DEFAULT ''::text
  crime_case_id			integer not null references forensics.crime_case,
  sex_id			integer references core.sex default null,
crime_case_party_role_id	integer not null references forensics.crime_case_party_role,
  crime_type_id			integer references forensics.crime_type default null,
  mental_disease_id		integer references forensics.mental_disease,
  crime_motive_id		integer references forensics.crime_motive,

  has_precedent_convictions	boolean not null default false,
  modus_operandi_id		integer references forensics.modus_operandi,
  consultancy_result_id		integer references forensics.consultancy_result,
  weapon_id			integer references forensics.weapon,
);*/
