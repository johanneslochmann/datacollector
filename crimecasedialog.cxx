#include "crimecasedialog.hxx"

#include <QDialogButtonBox>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QGroupBox>
#include <QFormLayout>

#include "datacollector.hxx"
#include "crimecasegateway.hxx"
#include "housingtypecombobox.hxx"

CrimeCaseDialog::CrimeCaseDialog(QWidget *p, CrimeCaseSPtr d)
    : QDialog(p), m_crimeCase(d)
{
    setLayout(new QVBoxLayout(this));

    createWidgets();
}

CrimeCaseDialog::~CrimeCaseDialog()
{
}

void CrimeCaseDialog::accept()
{
    if (CrimeCaseGateway().save(m_crimeCase)) {
        done(QDialog::Accepted);
    }
}

void CrimeCaseDialog::createWidgets()
{
    m_mainBox = new QGroupBox(tr("Crime Case"), this);
    m_mainBox->setLayout(new QGridLayout(m_mainBox));

    createCoreInfoBox();

    m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                     Qt::Horizontal,
                                     this);

    layout()->addWidget(m_mainBox);
    layout()->addWidget(m_buttons);

    connect(m_buttons, &QDialogButtonBox::accepted, this, &CrimeCaseDialog::accept);
    connect(m_buttons, &QDialogButtonBox::rejected, this, &CrimeCaseDialog::reject);
}

void CrimeCaseDialog::createCoreInfoBox()
{
    m_coreInfoBox = new QGroupBox(tr("Core Information"), m_mainBox);
    auto l = new QFormLayout(m_coreInfoBox);
    m_coreInfoBox->setLayout(l);

    m_name = new QLineEdit(m_crimeCase->name(), m_coreInfoBox);
    m_crimeYear = new QLineEdit(m_crimeCase->crimeYear().toString(), m_coreInfoBox);
    m_crimeDate = new QLineEdit(m_crimeCase->crimeDate().toString(), m_coreInfoBox);
    m_crimeTime = new QLineEdit(m_crimeCase->crimeTime().toString(), m_coreInfoBox);
    m_housingType = new HousingTypeComboBox(m_coreInfoBox);
    m_description = new QTextEdit(m_crimeCase->description(), m_coreInfoBox);

    l->addRow(tr("&Name"), m_name);
    l->addRow(tr("&Year"), m_crimeYear);
    l->addRow(tr("&Date [YYYY-MM-DD]"), m_crimeDate);
    l->addRow(tr("&Time [h:m]"), m_crimeTime);
    l->addRow(tr("&Housing Type"), m_housingType);
    l->addRow(tr("D&escription"), m_description);

    m_housingType->reload();

    if (m_crimeCase->housingType()->id() > 0) {
        m_housingType->setCurrentText(m_crimeCase->housingType()->name());
    }

    m_mainBox->layout()->addWidget(m_coreInfoBox);

    connect(m_name, &QLineEdit::textChanged, [=](const QString& s) { m_crimeCase->setName(s); });
    connect(m_crimeYear, &QLineEdit::textChanged, [=](const QString& s) { m_crimeCase->setCrimeYear(s.toInt()); });
    connect(m_crimeDate, &QLineEdit::textChanged, [=](const QString& s) { m_crimeCase->setCrimeDate(QDate::fromString(s, Qt::ISODate)); });
    connect(m_crimeTime, &QLineEdit::textChanged, [=](const QString& s) { m_crimeCase->setCrimeTime(QTime::fromString(s, "h:m")); });
    connect(m_description, &QTextEdit::textChanged, [=]() { m_crimeCase->setDescription(m_description->toPlainText()); });
    connect(m_housingType, &HousingTypeComboBox::currentHousingTypeChanged, [=](HousingTypeSPtr t) { m_crimeCase->setHousingType(t); });
}
