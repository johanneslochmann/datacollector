#pragma once

#include <QSqlRecord>

#include "agaterecord.hxx"

class AgateRecordGateway {
public:
    AgateRecordGateway();

    void save(AgateRecordSPtr r);

    AgateRecordSPtrVector loadAllInProject(ProjectSPtr p);
    AgateRecordSPtrVector loadAllInCampaign(CampaignSPtr c);

protected:

    void parse(AgateRecordSPtr ar, const QSqlRecord &rec);
};
