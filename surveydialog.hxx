#pragma once

#include <QDialog>
#include <QSqlQuery>
#include <QMap>

#include "project.hxx"
#include "campaign.hxx"
#include "survey.hxx"
#include "proband.hxx"
#include "organization.hxx"
#include "smokinghabit.hxx"

#include <memory>

class QSqlQueryModel;

namespace Ui {
class SurveyDialog;
}

class SurveyDialog : public QDialog
{
    Q_OBJECT

public:
    SurveyDialog(QWidget *parent, int defaultProjectId, int defaultCampaignId);
    ~SurveyDialog();

public slots:
    virtual void accept() override;

    virtual void onCurrentProjectChanged(const QString& projectName);
    virtual void onCurrentCampaignChanged(const QString& campaignName);
    virtual void onCurrentProbandChanged(const QString& label);
    virtual void onCurrentOrganizationChanged(const QString& name);
    virtual void onCurrentSmokingHabitChanged(const QString& name);
    virtual void onDescriptionChanged();

protected:
    virtual void loadProjects();
    virtual void loadProbands();
    virtual void loadOrganizations();
    virtual void loadSmokingHabits();

private:
    std::unique_ptr<Ui::SurveyDialog> ui;

    SurveySPtr m_data;

    int m_defaultProjectId;
    int m_defaultCampaignId;

    OrganizationSPtrVector m_organizations;
    ProbandSPtrVector m_probands;
    ProjectSPtrVector m_projects;
    CampaignSPtrVector m_campaigns;
    SmokingHabitSPtrVector m_smokingHabits;
};
