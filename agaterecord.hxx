#pragma once

#include "proband.hxx"
#include "organization.hxx"
#include "project.hxx"
#include "campaign.hxx"
#include "survey.hxx"
#include "sex.hxx"

class AgateRecord;
using AgateRecordSPtr = std::shared_ptr<AgateRecord>;
using AgateRecordSPtrVector = std::vector<AgateRecordSPtr>;

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

private:
    ProjectSPtr m_project;
    CampaignSPtr m_campaign;
    ProbandSPtr m_proband;
    OrganizationSPtr m_organization;
    SurveySPtr m_survey;
    SexSPtr m_sex;
};
