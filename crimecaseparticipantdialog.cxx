#include "crimecaseparticipantdialog.hxx"

#include <QGroupBox>
#include <QLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QIntValidator>

#include "datacollector.hxx"
#include "crimecasecombobox.hxx"
#include "crimecaseparticipantgateway.hxx"
#include "crimecasepartyrolecombobox.hxx"
#include "sexcombobox.hxx"
#include "crimetypecombobox.hxx"
#include "jobcombobox.hxx"
#include "crimemotivecombobox.hxx"
#include "mentaldiseasecombobox.hxx"
#include "modusoperandicombobox.hxx"

void CrimeCaseParticipantDialog::createDataWidgets()
{
    m_crimeCase = new CrimeCaseComboBox(m_b);
    if (m_participant->crimeCase()->id() > 0) {
        m_crimeCase->setCurrentText(m_participant->crimeCase()->name());
    }

    m_role = new CrimeCasePartyRoleComboBox(m_b);
    if (m_participant->role()->id() > 0) {
        m_role->setCurrentText(m_participant->role()->name());
    }

    m_sex = new SexComboBox(m_b);
    if(m_participant->sex()->id() > 0) {
        m_sex->setCurrentText(m_participant->sex()->name());
    }

    m_name = new QLineEdit(m_participant->name(), m_b);

    m_ageInYears = new QLineEdit(QString("%1").arg(m_participant->ageInYears()), m_b);
    m_ageInYears->setValidator(new QIntValidator(m_ageInYears));

    m_job = new JobComboBox(m_b);
    if (m_participant->job()->id() > 0) {
        m_job->setCurrentText(m_participant->job()->name());
    }

    m_crimeType = new CrimeTypeComboBox(m_b);
    if (m_participant->crimeType()->id() > 0) {
        m_crimeType->setCurrentText(m_participant->crimeType()->name());
    }

    m_motive = new CrimeMotiveComboBox(m_b);
    if (m_participant->motive()->id() > 0) {
        m_motive->setCurrentText(m_participant->motive()->name());
    }

    m_mentalDisease = new MentalDiseaseComboBox(m_b);
    if (m_participant->mentalDisease()->id() > 0) {
        m_mentalDisease->setCurrentText(m_participant->mentalDisease()->name());
    }

    m_modusOperandi = new ModusOperandiComboBox(m_b);
    if (m_participant->modusOperandi()->id() > 0) {
        m_modusOperandi->setCurrentText(m_participant->modusOperandi()->name());
    }

    m_description = new QTextEdit(m_participant->description(), m_b);
}

CrimeCaseParticipantDialog::CrimeCaseParticipantDialog(QWidget *p, CrimeCaseParticipantSPtr ccp)
    : QDialog(p), m_participant(ccp)
{
    setLayout(new QVBoxLayout(this));

    m_b = new QGroupBox("Crime Case Party", this);
    auto l = new QFormLayout(m_b);
    m_b->setLayout(l);

    createDataWidgets();

    l->addRow(tr("&Crime Case"), m_crimeCase);
    l->addRow(tr("&Role"), m_role);
    l->addRow(tr("&Sex"), m_sex);
    l->addRow(tr("&Name"), m_name);
    l->addRow(tr("&Age in Years"), m_ageInYears);
    l->addRow(tr("&Job"), m_job);
    l->addRow(tr("Crime &Type"), m_crimeType);
    l->addRow(tr("&Motive"), m_motive);
    l->addRow(tr("Modus &Operandi"), m_modusOperandi);
    l->addRow(tr("Mental Dis&ease"), m_mentalDisease);
    l->addRow(tr("&Description"), m_description);

    m_bb = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

    layout()->addWidget(m_b);
    layout()->addWidget(m_bb);

    connect(m_crimeCase, &CrimeCaseComboBox::currentCrimeCaseChanged, [=](CrimeCaseSPtr c) { m_participant->setCrimeCase(c); });
    connect(m_role, &CrimeCasePartyRoleComboBox::currentCrimeCasePartyRoleChanged, [=](CrimeCasePartyRoleSPtr r) { m_participant->setRole(r); });
    connect(m_sex, &SexComboBox::currentSexChanged, [=](SexSPtr s) { m_participant->setSex(s); });
    connect(m_crimeType, &CrimeTypeComboBox::currentCrimeTypeChanged, [=](CrimeTypeSPtr t) { m_participant->setCrimeType(t); });
    connect(m_motive, &CrimeMotiveComboBox::currentCrimeMotiveChanged, [=](CrimeMotiveSPtr m) { m_participant->setMotive(m); });
    connect(m_job, &JobComboBox::currentJobChanged, [=](JobSPtr j) { m_participant->setJob(j); });
    connect(m_mentalDisease, &MentalDiseaseComboBox::currentMentalDiseaseChanged, [=](MentalDiseaseSPtr s) { m_participant->setMentalDisease(s); });
    connect(m_modusOperandi, &ModusOperandiComboBox::currentModusOperandiChanged, [=](ModusOperandiSPtr m) { m_participant->setModusOperandi(m); });
    connect(m_name, &QLineEdit::textChanged, [=](const QString& v) { m_participant->setName(v); });
    connect(m_ageInYears, &QLineEdit::textChanged, [=](const QString& v) { m_participant->setAgeInYears(v.toInt()); });
    connect(m_description, &QTextEdit::textChanged, [=]() { m_participant->setDescription(m_description->toPlainText()); });

    connect(m_bb, &QDialogButtonBox::accepted, this, &CrimeCaseParticipantDialog::accept);
    connect(m_bb, &QDialogButtonBox::rejected, this, &CrimeCaseParticipantDialog::reject);
}

void CrimeCaseParticipantDialog::accept()
{
    try {
        CrimeCaseParticipantGateway().save(m_participant);
        done(QDialog::Accepted);
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to save Crime Case Participant"));
        DataCollector::get()->rollback();
    }
}
