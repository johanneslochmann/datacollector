#include "agatediagnosisdialog.hxx"

#include <QLayout>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QFormLayout>
#include <QMessageBox>

#include "diagnosisgateway.hxx"
#include "datagateway.h"

AgateDiagnosisDialog::AgateDiagnosisDialog(QWidget *p)
    : QDialog(p), m_d(std::make_shared<AgateDiagnosis>())
{
    configureUi();
}

AgateDiagnosisDialog::AgateDiagnosisDialog(QWidget *p, AgateDiagnosisSPtr d)
    : QDialog(p), m_d(d)
{
    configureUi();

    m_buffer.name = d->name;
    m_buffer.id = d->id;
}

void AgateDiagnosisDialog::accept()
{
    auto pdNameIdPair = m_diagnosis->currentSelectionNameIdPair();

    if (pdNameIdPair.name().isEmpty()) {
        QMessageBox::information(this, tr("Diagnosis missing"), tr("No diagnosis selected."));
        return;
    }

    try {
        pdNameIdPair.setId(DiagnosisGateway().loadIdFromName(pdNameIdPair.name()));
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load id of diagnosis: %1").arg(pdNameIdPair.name()), this);
        return;
    }

    m_d->name = pdNameIdPair.name();
    m_d->id = pdNameIdPair.id();

    done(QDialog::Accepted);
}

void AgateDiagnosisDialog::configureUi()
{
    setLayout(new QVBoxLayout());

    m_diagnosis = new Icd10DiagnosisManagementWidget(this);

    m_b = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

    layout()->addWidget(m_diagnosis);
    layout()->addWidget(m_b);

    connect(m_b, &QDialogButtonBox::accepted, this, &AgateDiagnosisDialog::accept);
    connect(m_b, &QDialogButtonBox::rejected, this, &AgateDiagnosisDialog::reject);
}

