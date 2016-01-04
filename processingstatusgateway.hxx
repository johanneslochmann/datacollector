#pragma once

#include "datagateway.h"

#include "processingstatus.hxx"

class ProcessingStatusGateway : public DataGateway<ProcessingStatus>
{
public:
    ProcessingStatusGateway() : DataGateway<ProcessingStatus>() {}

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
