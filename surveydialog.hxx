#pragma once

#include <QDialog>
#include <QSqlQuery>
#include <QMap>

#include "project.hxx"
#include "campaign.hxx"
#include "survey.hxx"

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

protected:
    virtual void loadProjects();
    virtual void save();

private:
    Ui::SurveyDialog *ui;

    Survey m_data;

    int m_defaultProjectId;
    int m_defaultCampaignId;

    ProjectSPtrVector m_projects;
    CampaignSPtrVector m_campaigns;
};
