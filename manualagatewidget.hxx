#pragma once

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>

#include "project.hxx"
#include "campaign.hxx"

class ProjectComboBox;
class CampaignComboBox;
class AgateSurveysTableWidget;

class ManualAgateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ManualAgateWidget(QWidget *parent = 0);

signals:

public slots:
    void onCurrentProjectChanged(ProjectSPtr p);
    void onCurrentCampaignChanged(CampaignSPtr c);

    void createSurvey();
    void editSurvey();
    void deleteSurvey();

private:
    void createFilterBox();
    void createSurveyListBox();
    void createCurrentSurveyBox();

    QGroupBox* m_filterBox;
    ProjectComboBox* m_projects;
    CampaignComboBox* m_campaigns;

    QGroupBox* m_surveyListBox;
    AgateSurveysTableWidget* m_agateSurveys;
    QPushButton* m_createSurvey;
    QPushButton* m_editSurvey;
    QPushButton* m_deleteSurvey;

    QGroupBox* m_currentSurveyBox;

    ProjectSPtr m_currentProject;
    CampaignSPtr m_currentCampaign;
};

