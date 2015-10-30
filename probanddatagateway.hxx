#pragma once

#include "datagateway.h"

#include "proband.hxx"

class ProbandDataGateway : public DataGateway<Proband>
{
public:
    ProbandDataGateway() : DataGateway<Proband>() {}

protected:
    QString loadAllQueryText() const override;
    void parse(ProbandSPtr t, const QSqlRecord &rec) override;
};

