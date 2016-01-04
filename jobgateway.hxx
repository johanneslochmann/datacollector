#pragma once

#include "datagateway.h"

#include "job.hxx"

class JobGateway : public DataGateway<Job>
{
public:
    JobGateway() : DataGateway<Job>() {}

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
