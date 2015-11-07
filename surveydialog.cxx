#include "surveydialog.hxx"
#include "ui_surveydialog.h"

#include <QMessageBox>
#include <QComboBox>
#include <QSqlQueryModel>
#include <QDebug>
#include <QDateEdit>
#include <QTextEdit>

#include "databaseerror.hxx"

#include "datacollector.hxx"
#include "projectdatagateway.hxx"
#include "campaigndatagateway.hxx"
#include "probanddatagateway.hxx"
#include "surveygateway.hxx"
#include "organizationgateway.hxx"
#include "smokinghabitgateway.hxx"

SurveyDialog::SurveyDialog(QWidget *parent, int defaultProjectId, int defaultCampaignId) :
    QDialog(parent),
    ui(std::unique_ptr<Ui::SurveyDialog>(new Ui::SurveyDialog)),
    m_defaultProjectId(defaultProjectId),
    m_defaultCampaignId(defaultCampaignId)
{
    m_data = std::make_shared<Survey>();

    ui->setupUi(this);

    ui->date->setDisplayFormat("dd.MM.yyyy");
    ui->date->setDate(QDate::currentDate());
    ui->date->setCalendarPopup(true);

    loadProbands();
    loadOrganizations();
    loadProjects();
    loadSmokingHabits();

    if (m_defaultProjectId > 0) {
        for (auto p : m_projects) {
            if (p->id() == m_defaultProjectId) {
                ui->project->setCurrentText(p->name());
            }
        }
    }

    if (m_defaultCampaignId) {
        onCurrentProjectChanged(ui->project->currentText());
        QCoreApplication::processEvents(); // load campaigns

        for (auto c : m_campaigns) {
            if (c->id() == m_defaultCampaignId) {
                ui->campaign->setCurrentText(c->name());
                m_data->setCampaignId(c->id());
            }
        }
    }

    for (auto h : m_smokingHabits) {
        if (m_data->smokingHabitId() == h->id()) {
            ui->smokingHabit->setCurrentText(h->name());
        }
    }

    connect(ui->project, SIGNAL(activated(QString)), this, SLOT(onCurrentProjectChanged(QString)));
    connect(ui->campaign, SIGNAL(activated(QString)), this, SLOT(onCurrentCampaignChanged(QString)));
    connect(ui->proband, SIGNAL(activated(QString)), this, SLOT(onCurrentProbandChanged(QString)));
    connect(ui->organization, SIGNAL(activated(QString)), this, SLOT(onCurrentOrganizationChanged(QString)));
    connect(ui->smokingHabit, SIGNAL(activated(QString)), this, SLOT(onCurrentSmokingHabitChanged(QString)));
    connect(ui->comment, SIGNAL(textChanged()), this, SLOT(onDescriptionChanged()));
}

SurveyDialog::~SurveyDialog()
{
}

void SurveyDialog::accept()
{
    try {
        SurveyGateway().save(m_data);
        done(QDialog::Accepted);
        DataCollector::get()->commit();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to save survey"), this);
        DataCollector::get()->rollback();
    }
}

void SurveyDialog::onCurrentProjectChanged(const QString &projectName)
{
    m_data->setCampaignId(0);

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

        ui->campaign->setCurrentText("");
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Campaigns in Project"), this);
    }
}

void SurveyDialog::onCurrentCampaignChanged(const QString &campaignName)
{
    m_data->setCampaignId(0);

    for (auto c : m_campaigns) {
        if (campaignName == c->name()) {
            m_data->setCampaignId(c->id());
        }
    }
}

void SurveyDialog::onCurrentProbandChanged(const QString &label)
{
    m_data->setProbandId(0);

    for (auto p : m_probands) {
        if (label == p->label()) {
            m_data->setProbandId(p->id());
        }
    }
}

void SurveyDialog::onCurrentOrganizationChanged(const QString &name)
{
    m_data->setOrganizationUnitId(0);

    for (auto o : m_organizations) {
        if (o->name() == name) {
            m_data->setOrganizationUnitId(o->id());
        }
    }
}

void SurveyDialog::onCurrentSmokingHabitChanged(const QString &name)
{
    m_data->setSmokingHabitId(0);

    for (auto o : m_smokingHabits) {
        if (o->name() == name) {
            m_data->setSmokingHabitId(o->id());
        }
    }
}

void SurveyDialog::onDescriptionChanged()
{
    m_data->setDescription(ui->comment->toPlainText());
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

void SurveyDialog::loadProbands()
{
    try {
        m_probands = ProbandDataGateway().loadAll();
        m_probands.push_back(std::make_shared<Proband>());

        ui->proband->clear();
        for (auto p : m_probands) {
            ui->proband->addItem(p->label(), p->id());
        }

        ui->proband->setCurrentText("");
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load probands."), this);
    }
}

void SurveyDialog::loadOrganizations()
{
    try {
        m_organizations = OrganizationGateway().loadAll();
        m_organizations.push_back(std::make_shared<Organization>());

        ui->organization->clear();
        for (auto p : m_organizations) {
            ui->organization->addItem(p->name(), p->id());
        }

        ui->organization->setCurrentText("");
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load organizations."), this);
    }
}

void SurveyDialog::loadSmokingHabits()
{
    try {
        m_smokingHabits = SmokingHabitGateway().loadAll();
        m_smokingHabits.push_back(std::make_shared<SmokingHabit>());

        ui->smokingHabit->clear();
        for (auto p : m_smokingHabits) {
            ui->smokingHabit->addItem(p->name(), p->id());
        }

        ui->smokingHabit->setCurrentText("");
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load smoking habits."), this);
    }
}

