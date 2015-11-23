#include "agatemedicationdialog.hxx"

#include <QLayout>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QFormLayout>
#include <QMessageBox>

#include "moleculegateway.hxx"
#include "datagateway.h"

AgateMedicationDialog::AgateMedicationDialog(QWidget *p)
    : QDialog(p), m_d(std::make_shared<AgateMedication>())
{
    configureUi();
}

AgateMedicationDialog::AgateMedicationDialog(QWidget *p, AgateMedicationSPtr d)
    : QDialog(p), m_d(d)
{
    configureUi();

    m_buffer.moleculeName = d->moleculeName;
    m_buffer.moleculeId = d->moleculeId;
    m_buffer.dosageInMg = d->dosageInMg;
}

void AgateMedicationDialog::accept()
{
    auto pdNameIdPair = m_molecules->currentSelectionNameIdPair();

    if (pdNameIdPair.name().isEmpty()) {
        QMessageBox::information(this, tr("Molecule missing"), tr("No molecule selected."));
        return;
    }

    try {
        pdNameIdPair.setId(MoleculeGateway().loadIdFromName(pdNameIdPair.name()));
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load id of molecule: %1").arg(pdNameIdPair.name()), this);
        return;
    }

    m_d->moleculeName = pdNameIdPair.name();
    m_d->moleculeId = pdNameIdPair.id();

    m_d->dosageInMg = m_buffer.dosageInMg;

    QMessageBox::information(this, "", tr("dosage: %1").arg(m_d->dosageInMg));

    done(QDialog::Accepted);
}

void AgateMedicationDialog::onDosisChanged(const QString &s)
{
    m_buffer.dosageInMg = s.toDouble();
}

void AgateMedicationDialog::configureUi()
{
    setLayout(new QVBoxLayout());

    m_molecules = new MoleculeManagementWidget(this);
    m_details = new QGroupBox(tr("Details"), this);
    m_dosageInMgW = new QLineEdit(m_details);
    m_dosageInMgW->setValidator(new QDoubleValidator(m_dosageInMgW));

    auto fl = new QFormLayout(m_details);
    fl->addRow(tr("Dosage in mg"), m_dosageInMgW);

    m_b = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

    layout()->addWidget(m_molecules);
    layout()->addWidget(m_details);
    layout()->addWidget(m_b);

    connect(m_b, &QDialogButtonBox::accepted, this, &AgateMedicationDialog::accept);
    connect(m_b, &QDialogButtonBox::rejected, this, &AgateMedicationDialog::reject);
    connect(m_dosageInMgW, &QLineEdit::textChanged, this, &AgateMedicationDialog::onDosisChanged);
}

