#include "manualagatewidget.hxx"

#include <QLayout>
#include <QDebug>
#include <QFormLayout>

#include "projectcombobox.hxx"
#include "campaigncombobox.hxx"
#include "agatesurveystablewidget.hxx"
#include "sexcombobox.hxx"
#include "agaterecorddialog.hxx"

#include "datacollector.hxx"

void ManualAgateWidget::createFilterBox()
{
    m_filterBox = new QGroupBox(tr("Filter"), this);
    auto l = new QFormLayout(m_filterBox);
    m_filterBox->setLayout(l);

    m_projectsFilter = new ProjectComboBox(m_filterBox);
    m_campaignsFilter = new CampaignComboBox(m_filterBox);

    l->addRow(tr("Show Only Project:"), m_projectsFilter);
    l->addRow(tr("Show Only Campaign:"), m_campaignsFilter);
}

void ManualAgateWidget::createDefaultBox()
{
    m_defaultBox = new QGroupBox("Defaults", this);
    auto l = new QFormLayout(m_defaultBox);
    m_defaultBox->setLayout(l);

    m_defaultProjects = new ProjectComboBox(m_defaultBox);
    m_defaultCampaigns = new CampaignComboBox(m_defaultBox);
    m_defaultSurveyDateW = new QCalendarWidget(m_defaultBox);
    m_defaultSurveyDateW->setSelectedDate(m_defaultSurveyDate);

    l->addRow(tr("Default Project"), m_defaultProjects);
    l->addRow(tr("Default Campaign"), m_defaultCampaigns);
    l->addRow(tr("Default Survey Date"), m_defaultSurveyDateW);
}

void ManualAgateWidget::createSurveyListBox()
{
    m_surveyListBox = new QGroupBox(tr("&Surveys"), this);
    m_agateSurveys = new AgateSurveysTableWidget(this);

    m_createSurvey = new QPushButton(tr("Create Survey"), m_surveyListBox);
    m_editSurvey = new QPushButton(tr("Edit Survey"), m_surveyListBox);
    m_deleteSurvey = new QPushButton(tr("Delete Survey"), m_surveyListBox);

    auto bl = new QHBoxLayout();
    bl->addWidget(m_createSurvey);
    bl->addWidget(m_editSurvey);
    bl->addWidget(m_deleteSurvey);

    m_surveyListBox->setLayout(new QVBoxLayout(m_surveyListBox));
    m_surveyListBox->layout()->addWidget(m_agateSurveys);
    m_surveyListBox->layout()->addItem(bl);

    connect(m_createSurvey, &QPushButton::clicked, this, &ManualAgateWidget::createSurvey);
    connect(m_editSurvey, &QPushButton::clicked, this, &ManualAgateWidget::editSurvey);
    connect(m_deleteSurvey, &QPushButton::clicked, this, &ManualAgateWidget::deleteSurvey);
}

ManualAgateWidget::ManualAgateWidget(QWidget *parent)
    : QWidget(parent)
{
    createFilterBox();
    createDefaultBox();
    createSurveyListBox();

    connect(m_projectsFilter, &ProjectComboBox::currentProjectChanged, m_campaignsFilter, &CampaignComboBox::onFilterChanged);

    connect(m_projectsFilter, &ProjectComboBox::currentProjectChanged, m_agateSurveys, &AgateSurveysTableWidget::onProjectChanged);
    connect(m_campaignsFilter, &CampaignComboBox::currentCampaignChanged, m_agateSurveys, &AgateSurveysTableWidget::onCampaignChanged);

    connect(m_defaultProjects, &ProjectComboBox::currentProjectChanged, m_defaultCampaigns, &CampaignComboBox::onFilterChanged);

    connect(m_defaultProjects, &ProjectComboBox::currentProjectChanged, this, &ManualAgateWidget::onDefaultProjectChanged);
    connect(m_defaultCampaigns, &CampaignComboBox::currentCampaignChanged, this, &ManualAgateWidget::onDefaultCampaignChanged);
    connect(m_defaultSurveyDateW, &QCalendarWidget::activated, this, &ManualAgateWidget::onDefaultDateChanged);

    setLayout(new QVBoxLayout(this));
    layout()->addWidget(m_filterBox);
    layout()->addWidget(m_defaultBox);
    layout()->addWidget(m_surveyListBox);
}

void ManualAgateWidget::onDefaultProjectChanged(ProjectSPtr p)
{
    m_defaultProject = p;
}

void ManualAgateWidget::onDefaultCampaignChanged(CampaignSPtr c)
{
    m_defaultCampaign = c;

    if (m_defaultCampaign) {
        if (m_defaultCampaign->begin().isValid()) {
            m_defaultSurveyDateW->setSelectedDate(m_defaultCampaign->begin());
        }
    }
}

void ManualAgateWidget::onDefaultDateChanged(const QDate &d)
{
    m_defaultSurveyDate = d;
}

void ManualAgateWidget::createSurvey()
{
    auto dlg = new AgateRecordDialog(this);
    dlg->setDefaultProject(m_defaultProject);
    dlg->setDefaultCampaign(m_defaultCampaign);
    dlg->setDefaultDate(m_defaultSurveyDate);

    if (QDialog::Accepted == dlg->exec()) {
        m_agateSurveys->reload();
        // TODO: scroll to new survey and select it
    }
}

void ManualAgateWidget::editSurvey()
{

}

void ManualAgateWidget::deleteSurvey()
{

}


