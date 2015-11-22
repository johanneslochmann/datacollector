#pragma once

#include <QSqlRecord>

#include "agaterecord.hxx"

class AgateRecordGateway {
public:
    AgateRecordGateway();

    void save(AgateRecordSPtr r);
    void remove(int surveyId);

    AgateRecordSPtrVector loadAllInProject(ProjectSPtr p);
    AgateRecordSPtrVector loadAllInCampaign(CampaignSPtr c);

protected:
    void createProband(ProbandSPtr p);
    void createSurvey(AgateRecordSPtr r);
    void deleteDiagnosisFromSurvey(AgateRecordSPtr r);
    void deleteDepotsFromSurvey(AgateRecordSPtr r);
    void deleteRegularPrescriptionsFromSurvey(AgateRecordSPtr r);
    void addDiagnosis(AgateRecordSPtr r);
    void addDepots(AgateRecordSPtr r);
    void addRegularPrescriptions(AgateRecordSPtr r);

    void parse(AgateRecordSPtr ar, const QSqlRecord &rec);
};
