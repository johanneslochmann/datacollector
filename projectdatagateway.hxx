#pragma once

#include "datagateway.h"

#include "project.hxx"

class ProjectDataGateway: public DataGateway<Project>
{
public:
    ProjectDataGateway(): DataGateway<Project>()
    {}

protected:
    QString loadAllQueryText() const override;
    void parse(std::shared_ptr<Project> t, const QSqlRecord &rec) override;
};


