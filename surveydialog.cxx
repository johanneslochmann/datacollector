#include "surveydialog.hxx"
#include "ui_surveydialog.h"

#include <QMessageBox>
#include <QComboBox>
#include <QSqlQueryModel>
#include <QDebug>

#include "databaseerror.hxx"

#include "datacollector.hxx"
#include "projectdatagateway.hxx"
#include "campaigndatagateway.hxx"

SurveyDialog::SurveyDialog(QWidget *parent, int defaultProjectId, int defaultCampaignId) :
    QDialog(parent),
    ui(new Ui::SurveyDialog),
    m_defaultProjectId(defaultProjectId),
    m_defaultCampaignId(defaultCampaignId)
{
    ui->setupUi(this);

    loadProjects();

    connect(ui->project, SIGNAL(activated(QString)), this, SLOT(onCurrentProjectChanged(QString)));
    connect(ui->campaign, SIGNAL(activated(QString)), this, SLOT(onCurrentCampaignChanged(QString)));
}

SurveyDialog::~SurveyDialog()
{
    delete ui;
}

void SurveyDialog::accept()
{
    try {
        save();
        done(QDialog::Accepted);
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to save survey"), this);
    }
}

void SurveyDialog::onCurrentProjectChanged(const QString &projectName)
{
    for (auto p : m_projects) {
        if (p->name() == projectName) {
            m_defaultProjectId = p->id();
        }
    }

    ui->campaign->clear();

    try {
        m_campaigns = CampaignDataGateway().campaignsInProject(m_defaultProjectId);
        m_campaigns.push_back(std::make_shared<Campaign>());

        for (auto c : m_campaigns) {
            ui->campaign->addItem(c->name(), c->id());
        }

        ui->project->setCurrentText("");
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Campaigns in Project"), this);
    }
}

void SurveyDialog::onCurrentCampaignChanged(const QString &campaignName)
{

}

void SurveyDialog::loadProjects()
{
    try {
        m_projects = ProjectDataGateway().loadAll();
        m_projects.push_back(std::make_shared<Project>());

        ui->project->clear();
        for (auto p : m_projects) {
            ui->project->addItem(p->name(), p->id());
        }

        ui->project->setCurrentText("");
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load survey for editing"), this);
        done(QDialog::Rejected);
    }
}

void SurveyDialog::save()
{
    if (m_data.hasId()) {
        // update
        return;
    }

    // insert
}

