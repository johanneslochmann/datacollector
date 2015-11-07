#pragma once

#include <QWidget>
#include <QSqlQuery>

#include "databaseerror.hxx"

#include <memory>

class QSqlQueryModel;

namespace Ui {
class SurveyForm;
}

class SurveyForm : public QWidget
{
    Q_OBJECT

public:
    explicit SurveyForm(QWidget *parent = 0);
    ~SurveyForm();

signals:
    void projectFilterChanged(int projectId);
    void campaignFilterChanged(int campaignId);
    void surveyFilterChanged(int surveyId);

public slots:
    void onDatabaseAboutToClose();
    void onDatabaseAvailable();
    void onDatabaseUnavailable();

    void onCurrentProjectChanged(const QString& name);
    void onCurrentCampaignChanged(const QString& name);
    void onCurrentSurveyChanged(const QModelIndex& idx);

    void onProjectFilterChanged(int projectId);
    void onCampaignFilterChanged(int campaignId);
    void onSurveyFilterChanged(int surveyId);

    void reload();

    void reloadSurveys();
    void createSurvey();

    void reloadIcd10Diagnosis();
    void addIcd10Diagnosis();
    void removeIcd10Diagnosis();

    void reloadOnDemandDrugs();
    void addOnDemandDrug();
    void removeOnDemandDrug();

    void reloadRegularDrugs();
    void addRegularDrug();
    void removeRegularDrug();

    void reloadPlasmaticLevels();
    void addPlasmaticLevel();
    void removePlasmaticLevel();

    void reloadDepotDrugs();
    void addDepotDrug();
    void removeDepotDrug();

    void reloadCollateralEffects();
    void addCollateralEffect();
    void removeCollateralEffect();

    void reloadCgi();
    void addCgi();
    void removeCgi();

protected:
    void prepareQueries();
    void setupModels();

    void showError(QSqlError err, const QString& msg);
    void showError(DatabaseError err);

private:
    std::unique_ptr<Ui::SurveyForm> ui;

    QSqlQuery m_projectsQry;
    QSqlQuery m_campaignsQry;
    QSqlQuery m_surveysQry;
    QSqlQuery m_icd10Qry;
    QSqlQuery m_onDemandDrugsQry;
    QSqlQuery m_reqularDrugsQry;
    QSqlQuery m_plasmaticLevelsQry;
    QSqlQuery m_depotDrugsQry;
    QSqlQuery m_collateralEffectsQry;
    QSqlQuery m_cgiQry;

    QSqlQuery m_getProjectIdQry;
    QSqlQuery m_getCampaignIdQry;

    QSqlQueryModel* m_projectsModel;
    QSqlQueryModel* m_campaignsModel;
    QSqlQueryModel* m_surveysModel;
    QSqlQueryModel* m_icd10Model;
    QSqlQueryModel* m_onDemandDrugsModel;
    QSqlQueryModel* m_reqularDrugsModel;
    QSqlQueryModel* m_plasmaticLevelsModel;
    QSqlQueryModel* m_depotDrugsModel;
    QSqlQueryModel* m_collateralEffectsModel;
    QSqlQueryModel* m_cgiModel;

    int m_currentProjectId { 0 };
    int m_currentCampaignId { 0 };
    int m_currentSurveyId { 0 };
};

