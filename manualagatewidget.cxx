#include "manualagatewidget.hxx"

#include <QLayout>
#include <QDebug>

#include "projectcombobox.hxx"
#include "campaigncombobox.hxx"
#include "agatesurveystablewidget.hxx"

#include "datacollector.hxx"

void ManualAgateWidget::createFilterBox()
{
    m_filterBox = new QGroupBox(tr("Filter"), this);
    m_filterBox->setLayout(new QHBoxLayout(m_filterBox));

    m_projects = new ProjectComboBox(m_filterBox);
    m_campaigns = new CampaignComboBox(m_filterBox);


    m_filterBox->layout()->addWidget(m_projects);
    m_filterBox->layout()->addWidget(m_campaigns);
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

void ManualAgateWidget::createCurrentSurveyBox()
{
    m_currentSurveyBox = new QGroupBox(tr("Current Survey"), this);

}

ManualAgateWidget::ManualAgateWidget(QWidget *parent)
    : QWidget(parent)
{
    createFilterBox();
    createSurveyListBox();
    createCurrentSurveyBox();

    connect(m_campaigns, &CampaignComboBox::currentCampaignChanged, this, &ManualAgateWidget::onCurrentCampaignChanged);
    connect(m_projects, &ProjectComboBox::currentProjectChanged, this, &ManualAgateWidget::onCurrentProjectChanged);

    connect(m_projects, &ProjectComboBox::currentProjectChanged, m_campaigns, &CampaignComboBox::onFilterChanged);

    connect(m_projects, &ProjectComboBox::currentProjectChanged, m_agateSurveys, &AgateSurveysTableWidget::onProjectChanged);
    connect(m_campaigns, &CampaignComboBox::currentCampaignChanged, m_agateSurveys, &AgateSurveysTableWidget::onCampaignChanged);

    setLayout(new QVBoxLayout(this));
    layout()->addWidget(m_filterBox);
    layout()->addWidget(m_surveyListBox);
    layout()->addWidget(m_currentSurveyBox);
}

void ManualAgateWidget::onCurrentProjectChanged(ProjectSPtr p)
{
    m_currentProject = p;

    qDebug() << "current project: " << (m_currentProject ? m_currentProject->name() : "<None>");
}

void ManualAgateWidget::onCurrentCampaignChanged(CampaignSPtr c)
{
    m_currentCampaign = c;

    qDebug() << "current campaign: " << (m_currentCampaign ? m_currentCampaign->name() : "<None>");
}

void ManualAgateWidget::createSurvey()
{

}

void ManualAgateWidget::editSurvey()
{

}

void ManualAgateWidget::deleteSurvey()
{

}


