#include "agatedepotdialog.hxx"

#include <QLayout>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QFormLayout>
#include <QMessageBox>

#include "prescribeabledruggateway.hxx"
#include "datagateway.h"

AgateDepotDialog::AgateDepotDialog(QWidget *p)
    : QDialog(p), m_d(std::make_shared<AgateDepot>())
{
    configureUi();
}

AgateDepotDialog::AgateDepotDialog(QWidget *p, AgateDepotSPtr d)
    : QDialog(p), m_d(d)
{
    configureUi();

    m_buffer.prescribeableDrugName = d->prescribeableDrugName;
    m_buffer.prescribeableDrugId = d->prescribeableDrugId;
    m_buffer.dosageInMg = d->dosageInMg;
    m_buffer.injectionIntervalInDays = d->injectionIntervalInDays;
    m_buffer.lastInjectionDate = d->lastInjectionDate;
}

void AgateDepotDialog::accept()
{
    auto pdNameIdPair = m_prescribeableDrugs->currentSelectionNameIdPair();

    if (pdNameIdPair.name().isEmpty()) {
        QMessageBox::information(this, tr("Prescribeable Drug missing"), tr("No drug selected."));
        return;
    }

    try {
        pdNameIdPair.setId(PrescribeableDrugGateway().loadIdFromName(pdNameIdPair.name()));
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load id of prescribeable drug: %1").arg(pdNameIdPair.name()), this);
        return;
    }

    m_d->prescribeableDrugName = pdNameIdPair.name();
    m_d->prescribeableDrugId = pdNameIdPair.id();

    m_d->dosageInMg = m_buffer.dosageInMg;
    m_d->injectionIntervalInDays = m_buffer.injectionIntervalInDays;
    m_d->lastInjectionDate = m_buffer.lastInjectionDate;

    done(QDialog::Accepted);
}

void AgateDepotDialog::onLastInjectionDateChanged(const QDate &d)
{
    m_buffer.lastInjectionDate = d;
}

void AgateDepotDialog::onDosisChanged(const QString &s)
{
    m_buffer.dosageInMg = s.toDouble();
}

void AgateDepotDialog::onIntervalChanged(const QString &i)
{
    m_buffer.injectionIntervalInDays = i.toInt();
}

void AgateDepotDialog::configureUi()
{
    setLayout(new QVBoxLayout());

    m_prescribeableDrugs = new PrescribeableDrugManagmentWidget(this);
    m_details = new QGroupBox(tr("Details"), this);
    m_lastInjectionW = new QCalendarWidget(m_details);
    m_dosageInMgW = new QLineEdit(m_details);
    m_dosageInMgW->setValidator(new QDoubleValidator(m_dosageInMgW));
    m_intervalInDaysW = new QLineEdit(m_details);
    m_intervalInDaysW->setValidator(new QIntValidator(m_intervalInDaysW));
    auto fl = new QFormLayout(m_details);
    fl->addRow(tr("Last Injection"), m_lastInjectionW);
    fl->addRow(tr("Dosage in mg"), m_dosageInMgW);
    fl->addRow(tr("Interval in Days"), m_intervalInDaysW);

    m_b = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

    layout()->addWidget(m_prescribeableDrugs);
    layout()->addWidget(m_details);
    layout()->addWidget(m_b);

    connect(m_b, &QDialogButtonBox::accepted, this, &AgateDepotDialog::accept);
    connect(m_b, &QDialogButtonBox::rejected, this, &AgateDepotDialog::reject);
    connect(m_lastInjectionW, &QCalendarWidget::activated, this, &AgateDepotDialog::onLastInjectionDateChanged);
    connect(m_dosageInMgW, &QLineEdit::textChanged, this, &AgateDepotDialog::onDosisChanged);
    connect(m_intervalInDaysW, &QLineEdit::textChanged, this, &AgateDepotDialog::onIntervalChanged);
}

