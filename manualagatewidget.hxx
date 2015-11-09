#pragma once

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QCalendarWidget>

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
    void onDefaultProjectChanged(ProjectSPtr p);
    void onDefaultCampaignChanged(CampaignSPtr c);
    void onDefaultDateChanged(const QDate& d);

    void createSurvey();
    void editSurvey();
    void deleteSurvey();

private:
    void createFilterBox();
    void createDefaultBox();
    void createSurveyListBox();
    void configurePersonalDataWidget(QGroupBox* b);

    QGroupBox* m_filterBox;
    ProjectComboBox* m_projectsFilter;
    CampaignComboBox* m_campaignsFilter;

    QGroupBox* m_defaultBox;
    ProjectComboBox* m_defaultProjects;
    CampaignComboBox* m_defaultCampaigns;
    QCalendarWidget* m_defaultSurveyDateW;

    QGroupBox* m_surveyListBox;
    AgateSurveysTableWidget* m_agateSurveys;
    QPushButton* m_createSurvey;
    QPushButton* m_editSurvey;
    QPushButton* m_deleteSurvey;

    ProjectSPtr m_defaultProject;
    CampaignSPtr m_defaultCampaign;
    QDate m_defaultSurveyDate { QDate::currentDate() };
};

