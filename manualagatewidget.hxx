#pragma once

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QDateEdit>

#include "project.hxx"
#include "campaign.hxx"
#include "organization.hxx"

class ProjectComboBox;
class CampaignComboBox;
class OrganizationComboBox;
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
    void onDefaultOrganizationChanged(OrganizationSPtr o);
    void onDefaultDateChanged(const QDate& d);

    void createSurvey();
    void editSurvey();
    void deleteSurvey();

private:
    void createFilterBox();
    void createDefaultBox();
    void createSurveyListBox();

    QGroupBox* m_filterBox;
    ProjectComboBox* m_projectsFilter;
    CampaignComboBox* m_campaignsFilter;

    QGroupBox* m_defaultBox;
    ProjectComboBox* m_defaultProjects;
    CampaignComboBox* m_defaultCampaigns;
    OrganizationComboBox* m_defaultOrganizations;
    QDateEdit* m_defaultSurveyDateW;

    QGroupBox* m_surveyListBox;
    AgateSurveysTableWidget* m_agateSurveys;
    QPushButton* m_createSurvey;
    QPushButton* m_editSurvey;
    QPushButton* m_deleteSurvey;

    ProjectSPtr m_defaultProject;
    CampaignSPtr m_defaultCampaign;
    OrganizationSPtr m_defaultOrganization;
    QDate m_defaultSurveyDate { QDate::currentDate() };
};

