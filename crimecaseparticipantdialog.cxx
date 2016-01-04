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

CrimeCaseParticipantDialog::CrimeCaseParticipantDialog(QWidget *p, CrimeCaseParticipantSPtr ccp)
    : QDialog(p), m_participant(ccp)
{
    setLayout(new QVBoxLayout(this));

    auto b = new QGroupBox("Crime Case Party", this);
    auto l = new QFormLayout(b);
    b->setLayout(l);

    m_crimeCase = new CrimeCaseComboBox(b);
    if (m_participant->crimeCase()->id() > 0) {
        m_crimeCase->setCurrentText(m_participant->crimeCase()->name());
    }

    m_role = new CrimeCasePartyRoleComboBox(b);
    if (m_participant->role()->id() > 0) {
        m_role->setCurrentText(m_participant->role()->name());
    }

    m_name = new QLineEdit(m_participant->name(), b);

    m_ageInYears = new QLineEdit(QString("%1").arg(m_participant->ageInYears()), b);
    m_ageInYears->setValidator(new QIntValidator(m_ageInYears));
    m_description = new QTextEdit(m_participant->description(), b);

    l->addRow(tr("&Crime Case"), m_crimeCase);
    l->addRow(tr("&Role"), m_role);
    l->addRow(tr("&Name"), m_name);
    l->addRow(tr("&Age in Years"), m_ageInYears);
    l->addRow(tr("&Description"), m_description);

    m_bb = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

    layout()->addWidget(b);
    layout()->addWidget(m_bb);

    connect(m_crimeCase, &CrimeCaseComboBox::currentCrimeCaseChanged, [=](CrimeCaseSPtr c) { m_participant->setCrimeCase(c); });
    connect(m_role, &CrimeCasePartyRoleComboBox::currentCrimeCasePartyRoleChanged, [=](CrimeCasePartyRoleSPtr r) { m_participant->setRole(r); });
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
