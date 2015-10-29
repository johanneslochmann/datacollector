#pragma once

#include "datagateway.h"

#include "campaign.hxx"

class CampaignDataGateway: public DataGateway<Campaign>
{
public:
    CampaignDataGateway(): DataGateway<Campaign>() {}

    CampaignSPtrVector campaignsInProject(int projectId);

protected:
    QString loadAllQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
