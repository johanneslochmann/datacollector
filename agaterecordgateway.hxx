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
    void createProband(ProbandSPtr p);
    void createSurvey(AgateRecordSPtr r);
    void deleteDiagnosisFromSurvey(AgateRecordSPtr r);
    void deleteDepotsFromSurvey(AgateRecordSPtr r);
    void addDiagnosis(AgateRecordSPtr r);
    void addDepots(AgateRecordSPtr r);

    void parse(AgateRecordSPtr ar, const QSqlRecord &rec);
};
