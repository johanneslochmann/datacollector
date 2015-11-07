#pragma once

#include "datagateway.h"

#include "survey.hxx"

class SurveyGateway : public DataGateway<Survey>
{
public:
    SurveyGateway() : DataGateway<Survey>() {}

    void save(SurveySPtr s);

    void addIcd10DiagnosisToSurvey(int icd10DiagnosisId, const QString& comment, int surveyId);
    void addCollateralEffectToSurvey(int effectId, const QString& comment, int surveyId);
    void addOnDemandDrugToSurvey(int drugId, const QString &description, int surveyId);
    void addRegularDrugToSurvey(int prescribeableDrugId, double morning, double lunch, double noon, double night, const QString &description, int surveyId);
    void addPlasmaticLevelToSurvey(int moleculeId, double value, const QString& unitName, const QString& comment, int surveyId);
    void addDepotDrugToSurvey(int prescribeableDrugId, double dosage, const QDate& lastInjection, int interval, const QString &comment, int surveyId);
    void addCgiToSurvey(double severity, double improvement, const QString& description, int surveyId);
    void addGafToSurvey(double value, const QString& description, int surveyId);
    void addFpsToSurvey(double value, const QString& description, int surveyId);
    void addWhoQolToSurvey(double physical, double psychological, double social, double environmental, const QString& description, int surveyId);

    void removeIcd10DiagnosisFromSurvey(int recordId);
    void removeCollateralEffectFromSurvey(int recordId);
    void removeOnDemandDrugFromSurvey(int recordId);
    void removeRegularDrugFromSurvey(int recordId);
    void removePlasmaticLevelFromSurvey(int recordId);
    void removeDepotDrugFromSurvey(int recordId);
    void removeCgiFromSurvey(int recordId);
    void removeGafFromSurvey(int recordId);
    void removeFpsFromSurvey(int recordId);
    void removeWhoQolFromSurvey(int recordId);

protected:
    QString loadAllQueryText() const override;
    void parse(SurveySPtr t, const QSqlRecord &rec) override;
    void insert(SurveySPtr s);
    void update(SurveySPtr s);
};


