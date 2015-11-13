#include "agaterecorddialog.hxx"

#include <QCoreApplication>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QIntValidator>
#include <QMessageBox>

#include "agaterecordgateway.hxx"
#include "datacollector.hxx"

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
    if (!validate()) {
        return;
    }

    try {
        AgateRecordGateway().save(m_r);
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to save AGATE Record"), this);
        return;
    }

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
    m_r->proband()->setYearOfBirth(y.toInt());
}

void AgateRecordDialog::onSexChanged(SexSPtr s)
{
    if (s && s->hasId()) {
        m_r->sex()->setId(s->id());
        m_r->sex()->setName(s->name());
        m_r->proband()->setSexId(s->id());
    } else {
        m_r->sex()->setId(0);
        m_r->sex()->setName("");
        m_r->proband()->setSexId(0);
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
    configureDiagnosisBox();
    configureDepotBox();
    configureMedicationBox();

    rootGrid->addWidget(m_surveyBox, 0, 0);
    rootGrid->addWidget(m_personalBox, 0, 1);
    rootGrid->addWidget(m_diagnosisBox, 0, 2);
    rootGrid->addWidget(m_depotBox, 1, 0, 1, 2);
    rootGrid->addWidget(m_medicationBox, 1, 2);

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

void AgateRecordDialog::configureMedicationBox()
{
    m_medicationBox = new QGroupBox(tr("Medication"), m_rootBox);
    m_medicationBox->setLayout(new QHBoxLayout(m_medicationBox));

    m_medications = new AgateMedicationTableWidget(m_medicationBox, m_r);
    m_addMedication = new QPushButton(tr("Add..."), m_medicationBox);
    m_removeMedication = new QPushButton(tr("Remove"), m_medicationBox);

    auto l = new QVBoxLayout();
    l->addWidget(m_addMedication);
    l->addStretch();
    l->addWidget(m_removeMedication);

    m_medicationBox->layout()->addWidget(m_medications);
    m_medicationBox->layout()->addItem(l);

    connect(m_addMedication, &QPushButton::clicked, m_medications, &AgateMedicationTableWidget::create);
    connect(m_removeMedication, &QPushButton::clicked, m_medications, &AgateMedicationTableWidget::remove);
}

void AgateRecordDialog::configureDiagnosisBox()
{

    m_diagnosisBox = new QGroupBox(tr("Diagnosis"), m_rootBox);
    m_diagnosisBox->setLayout(new QHBoxLayout(m_diagnosisBox));

    m_diagnosis = new AgateDiagnosisTableWidget(m_diagnosisBox, m_r);
    m_addDiagnosis = new QPushButton(tr("Add..."), m_diagnosisBox);
    m_removeDiagnosis = new QPushButton(tr("Remove"), m_diagnosisBox);

    auto l = new QVBoxLayout();
    l->addWidget(m_addDiagnosis);
    l->addStretch();
    l->addWidget(m_removeDiagnosis);

    m_diagnosisBox->layout()->addWidget(m_diagnosis);
    m_diagnosisBox->layout()->addItem(l);

    connect(m_addDiagnosis, &QPushButton::clicked, m_diagnosis, &AgateDiagnosisTableWidget::create);
    connect(m_removeDiagnosis, &QPushButton::clicked, m_diagnosis, &AgateDiagnosisTableWidget::remove);
}

bool AgateRecordDialog::validate()
{
    QStringList errors;

    if (m_r->campaign()->id() <= 0) {
        errors.append(tr("Campaign is missing"));
    }

    if (m_r->organization()->id() <= 0) {
        errors.append(tr("Organization is missing"));
    }

    if (m_r->proband()->yearOfBirth() <= 0) {
        errors.append(tr("Year of birth is missing"));
    }

    if (m_r->sex()->id() <= 0) {
        errors.append(tr("Sex is missing"));
    }

    if (!m_r->survey()->date().isValid()) {
        errors.append(tr("Survey date is missing."));
    }

    if (!errors.isEmpty()) {
        QMessageBox::critical(this, tr("Data incomplete"), tr("<p>Data is incomplete:</p><p>%1</p>").arg(errors.join("\n")));
        return false;
    }

    return true;
}

