#pragma once

#include "proband.hxx"
#include "organization.hxx"

class AgateRecord;
using AgateRecordSPtr = std::shared_ptr<AgateRecord>;
using AgateRecordSPtrVector = std::vector<AgateRecordSPtr>;

class AgateRecord
{
public:
    explicit AgateRecord();

    ProbandSPtr proband() const { return m_proband; }
    OrganizationSPtr organization() const { return m_organization; }

private:
    ProbandSPtr m_proband;
    OrganizationSPtr m_organization;
};
