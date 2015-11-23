#pragma once

#include <QSqlRecord>

#include "agaterecord.hxx"

class AgateRecordGateway {
public:
    AgateRecordGateway();

    void save(AgateRecordSPtr r);
    void remove(int surveyId);

    AgateRecordSPtr loadById(int id);
    AgateRecordSPtrVector loadAllInProject(ProjectSPtr p);
    AgateRecordSPtrVector loadAllInCampaign(CampaignSPtr c);

protected:
    void loadDetails(AgateRecordSPtr r);
    void loadDiagnosis(AgateRecordSPtr r);
    void loadDepots(AgateRecordSPtr r);
    void loadMoleculePrescriptions(AgateRecordSPtr r);

    void createProband(ProbandSPtr p);
    void createSurvey(AgateRecordSPtr r);
    void deleteDiagnosisFromSurvey(AgateRecordSPtr r);
    void deleteDepotsFromSurvey(AgateRecordSPtr r);
    void deleteRegularPrescriptionsFromSurvey(AgateRecordSPtr r);
    void addDiagnosis(AgateRecordSPtr r);
    void addDepots(AgateRecordSPtr r);
    void addMoleculePrescriptions(AgateRecordSPtr r);

    void parse(AgateRecordSPtr ar, const QSqlRecord &rec);
};
