#pragma once

#include "proband.hxx"
#include "organization.hxx"
#include "project.hxx"
#include "campaign.hxx"
#include "survey.hxx"
#include "sex.hxx"

class AgateRecord;
struct AgateDepot;

using AgateRecordSPtr = std::shared_ptr<AgateRecord>;
using AgateDepotSPtr = std::shared_ptr<AgateDepot>;

using AgateRecordSPtrVector = std::vector<AgateRecordSPtr>;
using AgateDepotSPtrVector = std::vector<AgateDepotSPtr>;

struct AgateDepot {
    QString prescribeableDrugName { "" };
    int prescribeableDrugId { 0 };
    QDate lastInjectionDate { QDate::currentDate() };
    double dosageInMg { 0.0 };
    int injectionIntervalInDays { 0 };
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

    void addDepot(AgateDepotSPtr d) { m_depots.push_back(d); }
    void removeDepot(int idx);

private:
    ProjectSPtr m_project;
    CampaignSPtr m_campaign;
    ProbandSPtr m_proband;
    OrganizationSPtr m_organization;
    SurveySPtr m_survey;
    SexSPtr m_sex;

    AgateDepotSPtrVector m_depots;
};
