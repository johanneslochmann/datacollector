#pragma once

#include "proband.hxx"
#include "organization.hxx"
#include "project.hxx"
#include "campaign.hxx"
#include "survey.hxx"
#include "sex.hxx"

class AgateRecord;
struct AgateDepot;
struct AgateMedication;
struct AgateDiagnosis;

using AgateRecordSPtr = std::shared_ptr<AgateRecord>;
using AgateDepotSPtr = std::shared_ptr<AgateDepot>;
using AgateMedicationSPtr = std::shared_ptr<AgateMedication>;
using AgateDiagnosisSPtr = std::shared_ptr<AgateDiagnosis>;

using AgateRecordSPtrVector = std::vector<AgateRecordSPtr>;
using AgateDepotSPtrVector = std::vector<AgateDepotSPtr>;
using AgateMedicationSPtrVector = std::vector<AgateMedicationSPtr>;
using AgateDiagnosisSPtrVector = std::vector<AgateDiagnosisSPtr>;

struct AgateDepot {
    QString prescribeableDrugName { "" };
    int prescribeableDrugId { 0 };
    QDate lastInjectionDate { QDate::currentDate() };
    double dosageInMg { 0.0 };
    int injectionIntervalInDays { 0 };
};

struct AgateMedication {
    QString moleculeName { "" };
    int moleculeId { 0 };
    double dosageInMg { 0.0 };
};

struct AgateDiagnosis {
    QString name { "" };
    int id { 0 };
};

class AgateRecord
{
public:
    explicit AgateRecord();

    ProjectSPtr project() const { return m_project; }
    CampaignSPtr campaign() const { return m_campaign; }
    ProbandSPtr proband() const { return m_proband; }
    OrganizationSPtr organization() const { return m_organization; }
    SurveySPtr survey() const { return m_survey; }
    SexSPtr sex() const { return m_sex; }

    AgateDepotSPtrVector depots() const { return m_depots; }
    AgateMedicationSPtrVector medication() const { return m_medication; }
    AgateDiagnosisSPtrVector diagnosis() const { return m_diagnosis; }

    void addDepot(AgateDepotSPtr d) { m_depots.push_back(d); }
    void addMedication(AgateMedicationSPtr m) { m_medication.push_back(m); }
    void addDiagnosis(AgateDiagnosisSPtr d) { m_diagnosis.push_back(d); }

    void removeDepot(int idx);
    void removeMedication(int idx);
    void removeDiagnosis(int idx);

private:
    ProjectSPtr m_project;
    CampaignSPtr m_campaign;
    ProbandSPtr m_proband;
    OrganizationSPtr m_organization;
    SurveySPtr m_survey;
    SexSPtr m_sex;

    AgateDepotSPtrVector m_depots;
    AgateMedicationSPtrVector m_medication;
    AgateDiagnosisSPtrVector m_diagnosis;
};
