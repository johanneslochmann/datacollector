#pragma once

#include <QWidget>
#include <QSqlQuery>

#include "databaseerror.hxx"

class QSqlQueryModel;

namespace Ui {
class AgateForm;
}

class AgateForm : public QWidget
{
    Q_OBJECT

public:
    explicit AgateForm(QWidget *parent = 0);
    ~AgateForm();

signals:
    void projectFilterChanged(int projectId);
    void campaignFilterChanged(int campaignId);
    void surveyFilterChanged(int surveyId);

public slots:
    void onCurrentProjectChanged(const QString& name);
    void onCurrentCampaignChanged(const QString& name);
    void onCurrentSurveyChanged(const QModelIndex& idx);

    void onProjectFilterChanged(int projectId);
    void onCampaignFilterChanged(int campaignId);
    void onSurveyFilterChanged(int surveyId);

    void reload();

    void reloadSurveys();
    void createSurvey();

protected:
    void prepareQueries();
    void setupModels();

    void showError(QSqlError err, const QString& msg);
    void showError(DatabaseError err);

private:
    Ui::AgateForm *ui;

    QSqlQuery m_projectsQry;
    QSqlQuery m_campaignsQry;
    QSqlQuery m_surveysQry;
    QSqlQuery m_icd10Qry;
    QSqlQuery m_ipOnDemandQry;
    QSqlQuery m_ipReqularQry;
    QSqlQuery m_ipPlasmaticLevelQry;
    QSqlQuery m_agateQry;

    QSqlQuery m_getProjectIdQry;
    QSqlQuery m_getCampaignIdQry;

    QSqlQueryModel* m_projectsModel;
    QSqlQueryModel* m_campaignsModel;
    QSqlQueryModel* m_surveysModel;
    QSqlQueryModel* m_icd10Model;
    QSqlQueryModel* m_ipOnDemandModel;
    QSqlQueryModel* m_ipReqularModel;
    QSqlQueryModel* m_ipPlasmaticLevelModel;
    QSqlQueryModel* m_agateModel;

    int m_currentProjectId { 0 };
    int m_currentCampaignId { 0 };
};

