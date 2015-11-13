#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QCalendarWidget>

#include "agaterecord.hxx"

#include "icd10diagnosismanagementwidget.hxx"

class AgateDiagnosisDialog : public QDialog
{
public:
    explicit AgateDiagnosisDialog(QWidget* p);
    explicit AgateDiagnosisDialog(QWidget* p, AgateDiagnosisSPtr d);

    AgateDiagnosisSPtr Diagnosis() const { return m_d; }

signals:

public slots:
    void accept();
    void onDosisChanged(const QString& s);

protected:
    void configureUi();

private:
    AgateDiagnosisSPtr m_d;

    Icd10DiagnosisManagementWidget* m_diagnosis;

    QDialogButtonBox* m_b;

    AgateDiagnosis m_buffer;
};

