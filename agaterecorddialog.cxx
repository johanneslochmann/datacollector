#include "agaterecorddialog.hxx"

#include <QCoreApplication>
#include <QLayout>
#include <QFormLayout>

AgateRecordDialog::AgateRecordDialog(QWidget* p)
    : QDialog(p),
      m_r(std::make_shared<AgateRecord>())
{
    configureUi();
}

AgateRecordDialog::AgateRecordDialog(QWidget *p, AgateRecordSPtr r)
    : QDialog(p),
      m_r(r)
{
    configureUi();
}

void AgateRecordDialog::setDefaultProject(ProjectSPtr p)
{
    m_defaultProject = p;

    m_projects->reload();

    if (!m_defaultProject) {
        return;
    }

    m_projects->setCurrentText(m_defaultProject->name());
    QCoreApplication::processEvents();
}

void AgateRecordDialog::setDefaultCampaign(CampaignSPtr c)
{
    m_defaultCampaign = c;

    m_campaigns->reload();

    if (!m_defaultCampaign) {
        return;
    }

    m_campaigns->setCurrentText(m_defaultCampaign->name());
    QCoreApplication::processEvents();
}

void AgateRecordDialog::accept()
{
    done(QDialog::Accepted);
}

void AgateRecordDialog::reject()
{
    done(QDialog::Rejected);
}

void AgateRecordDialog::configureUi()
{
    setLayout(new QVBoxLayout(this));

    m_rootBox = new QGroupBox(tr("AGATE Record"), this);
    auto rootGrid = new QGridLayout(m_rootBox);
    m_rootBox->setLayout(rootGrid);

    configureSurveyBox();
    configurePersonalBox();

    rootGrid->addWidget(m_surveyBox, 0, 0);
    rootGrid->addWidget(m_personalBox, 0, 1);

    m_b = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

    layout()->addWidget(m_rootBox);
    layout()->addWidget(m_b);

    connect(m_b, &QDialogButtonBox::accepted, this, &AgateRecordDialog::accept);
    connect(m_b, &QDialogButtonBox::rejected, this, &AgateRecordDialog::reject);
}

void AgateRecordDialog::configureSurveyBox()
{
    m_surveyBox = new QGroupBox(tr("Survey"), m_rootBox);
    m_projects = new ProjectComboBox(m_surveyBox);
    m_campaigns = new CampaignComboBox(m_surveyBox);

    connect(m_projects, &ProjectComboBox::currentProjectChanged, m_campaigns, &CampaignComboBox::onFilterChanged);

    auto l = new QFormLayout(m_surveyBox);
    m_surveyBox->setLayout(l);

    l->addRow(tr("Project"), m_projects);
    l->addRow(tr("Campaign"), m_campaigns);

    m_projects->reload();
}

void AgateRecordDialog::configurePersonalBox()
{
    m_personalBox = new QGroupBox(tr("Personal"), m_rootBox);
    auto l = new QFormLayout(m_personalBox);

    m_sexes = new SexComboBox(m_personalBox);
    l->addRow(tr("Sex"), m_sexes);
    m_sexes->reload();
}

