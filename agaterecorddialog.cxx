#include "agaterecorddialog.hxx"

#include <QCoreApplication>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QIntValidator>

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

void AgateRecordDialog::setDefaultDate(const QDate &d)
{
    m_defaultDate = d;

    if (m_defaultDate.isValid()) {
        m_surveyDate->setSelectedDate(m_defaultDate);
    } else {
        m_surveyDate->showToday();
    }

    QCoreApplication::processEvents();
}

void AgateRecordDialog::setDefaultOrganization(OrganizationSPtr o)
{
    m_defaultOrganization = o;

    m_organizations->reload();

    if (!m_defaultOrganization) {
        return;
    }

    m_organizations->setCurrentText(m_defaultOrganization->name());
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

void AgateRecordDialog::onProjectChanged(ProjectSPtr p)
{
    if (p && p->hasId()) {
        m_r->project()->setId(p->id());
        m_r->project()->setName(p->name());
    } else {
        m_r->project()->setId(0);
        m_r->project()->setName("");
    }
}

void AgateRecordDialog::onCampaignChanged(CampaignSPtr c)
{
    if (c && c->hasId()) {
        m_r->campaign()->setId(c->id());
        m_r->campaign()->setName(c->name());
    } else {
        m_r->campaign()->setId(0);
        m_r->campaign()->setName("");
    }
}

void AgateRecordDialog::onOrganizationChanged(OrganizationSPtr o)
{
    if (o && o->hasId()) {
        m_r->organization()->setId(o->id());
        m_r->organization()->setName(o->name());
    } else {
        m_r->organization()->setId(0);
        m_r->organization()->setName("");
    }
}

void AgateRecordDialog::onSurveyDateChanged(const QDate &d)
{
    m_r->survey()->setDate(d);
}

void AgateRecordDialog::onBirthYearChanged(const QString &y)
{
    m_r->proband()->setBirthday(QDate(y.toInt(), 1, 1));
}

void AgateRecordDialog::onSexChanged(SexSPtr s)
{
    if (s && s->hasId()) {
        m_r->sex()->setId(s->id());
        m_r->sex()->setName(s->name());
    } else {
        m_r->sex()->setId(0);
        m_r->sex()->setName("");
    }
}

void AgateRecordDialog::configureUi()
{
    setLayout(new QVBoxLayout(this));

    m_rootBox = new QGroupBox(tr("AGATE Record"), this);
    auto rootGrid = new QGridLayout(m_rootBox);
    m_rootBox->setLayout(rootGrid);

    configureSurveyBox();
    configurePersonalBox();
    configureDepotBox();

    rootGrid->addWidget(m_surveyBox, 0, 0);
    rootGrid->addWidget(m_personalBox, 0, 1);
    rootGrid->addWidget(m_depotBox, 1, 0);

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
    m_organizations = new OrganizationComboBox(m_surveyBox);
    m_surveyDate = new QCalendarWidget(m_surveyBox);

    connect(m_projects, &ProjectComboBox::currentProjectChanged, m_campaigns, &CampaignComboBox::onFilterChanged);

    connect(m_projects, &ProjectComboBox::currentProjectChanged, this, &AgateRecordDialog::onProjectChanged);
    connect(m_campaigns, &CampaignComboBox::currentCampaignChanged, this, &AgateRecordDialog::onCampaignChanged);
    connect(m_surveyDate, &QCalendarWidget::activated, this, &AgateRecordDialog::onSurveyDateChanged);
    connect(m_organizations, &OrganizationComboBox::currentOrganizationChanged, this, &AgateRecordDialog::onOrganizationChanged);

    auto l = new QFormLayout(m_surveyBox);
    m_surveyBox->setLayout(l);

    l->addRow(tr("Project"), m_projects);
    l->addRow(tr("Campaign"), m_campaigns);
    l->addRow(tr("Organization"), m_organizations);
    l->addRow(tr("Survey Date"), m_surveyDate);

    m_projects->reload();
}

void AgateRecordDialog::configurePersonalBox()
{
    m_personalBox = new QGroupBox(tr("Personal"), m_rootBox);
    auto l = new QFormLayout(m_personalBox);

    m_birthYear = new QLineEdit(m_personalBox);
    m_birthYear->setValidator(new QIntValidator(this));
    m_sexes = new SexComboBox(m_personalBox);

    connect(m_sexes, &SexComboBox::currentSexChanged, this, &AgateRecordDialog::onSexChanged);
    connect(m_birthYear, &QLineEdit::textChanged, this, &AgateRecordDialog::onBirthYearChanged);

    l->addRow(tr("Year Of Birth"), m_birthYear);
    l->addRow(tr("Sex"), m_sexes);
    m_sexes->reload();
}

void AgateRecordDialog::configureDepotBox()
{
    m_depotBox = new QGroupBox(tr("Depot"), m_rootBox);
    m_depotBox->setLayout(new QHBoxLayout(m_depotBox));

    m_depots = new AgateDepotTableWidget(m_depotBox, m_r);
    m_addDepot = new QPushButton(tr("Add..."), m_depotBox);
    m_removeDepot = new QPushButton(tr("Remove"), m_depotBox);

    auto l = new QVBoxLayout();
    l->addWidget(m_addDepot);
    l->addStretch();
    l->addWidget(m_removeDepot);

    m_depotBox->layout()->addWidget(m_depots);
    m_depotBox->layout()->addItem(l);

    connect(m_addDepot, &QPushButton::clicked, m_depots, &AgateDepotTableWidget::create);
    connect(m_removeDepot, &QPushButton::clicked, m_depots, &AgateDepotTableWidget::remove);
}

