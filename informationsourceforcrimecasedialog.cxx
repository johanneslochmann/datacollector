#include "informationsourceforcrimecasedialog.hxx"

#include <QDialogButtonBox>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>

#include "informationsourceforcrimecasegateway.hxx"
#include "crimecasecombobox.hxx"
#include "informationsourcetypecombobox.hxx"

InformationSourceForCrimeCaseDialog::InformationSourceForCrimeCaseDialog(QWidget *p, InformationSourceForCrimeCaseSPtr data)
    : QDialog(p), m_data(data)
{
    setLayout(new QVBoxLayout(this));

    m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

    auto b = new QGroupBox(tr("Information Source For Crime Case"), this);
    auto l = new QFormLayout(b);
    b->setLayout(l);

    m_crimeCases = new CrimeCaseComboBox(b);
    m_sourceTypes = new InformationSourceTypeComboBox(b);
    m_url = new QLineEdit(m_data->url(), b);
    m_when = new QDateTimeEdit(m_data->whenAdded(), b);
    m_description = new QTextEdit(b);
    m_description->setText(m_data->description());

    l->addRow(tr("&Crime Case"), m_crimeCases);
    l->addRow(tr("&Information Source Type"), m_sourceTypes);
    l->addRow(tr("&URL"), m_url);
    l->addRow(tr("&When Added"), m_when);
    l->addRow(tr("&Description"), m_description);

    if (m_data->crimeCase()->id() > 0) {
        m_crimeCases->setCurrentText(m_data->crimeCase()->name());
    }

    if (m_data->informationSourceType()->id() > 0) {
        m_sourceTypes->setCurrentText(m_data->informationSourceType()->name());
    }

    layout()->addWidget(b);
    layout()->addWidget(m_buttons);

    connect(m_crimeCases, &CrimeCaseComboBox::currentCrimeCaseChanged, [=](CrimeCaseSPtr c) { m_data->setCrimeCase(c); });
    connect(m_sourceTypes, &InformationSourceTypeComboBox::currentInformationSourceTypeChanged, [=](InformationSourceTypeSPtr t) { m_data->setInformationSourceType(t); });
    connect(m_url, &QLineEdit::textChanged, [=](const QString& s) { m_data->setUrl( s); });
    connect(m_when, &QDateTimeEdit::dateTimeChanged, [=](const QDateTime& t) { m_data->setWhenAdded(t); });
    connect(m_description, &QTextEdit::textChanged, [=]() { m_data->setDescription(m_description->toPlainText()); });

    connect(m_buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void InformationSourceForCrimeCaseDialog::accept()
{
    try {
        InformationSourceForCrimeCaseGateway().save(m_data);
        done(QDialog::Accepted);
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to save information source for crime case"), this);
        DataCollector::get()->rollback();
    }
}
