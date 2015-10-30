#pragma once

#include "datagateway.h"

#include "survey.hxx"

class SurveyGateway : public DataGateway<Survey>
{
public:
    SurveyGateway() : DataGateway<Survey>() {}

    void save(SurveySPtr s);

protected:
    QString loadAllQueryText() const override;
    void parse(SurveySPtr t, const QSqlRecord &rec) override;
    void insert(SurveySPtr s);
    void update(SurveySPtr s);
};