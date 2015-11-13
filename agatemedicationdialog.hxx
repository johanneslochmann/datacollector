#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QCalendarWidget>

#include "agaterecord.hxx"

#include "moleculemanagementwidget.hxx"

class AgateMedicationDialog : public QDialog
{
public:
    explicit AgateMedicationDialog(QWidget* p);
    explicit AgateMedicationDialog(QWidget* p, AgateMedicationSPtr d);

    AgateMedicationSPtr Medication() const { return m_d; }

signals:

public slots:
    void accept();
    void onDosisChanged(const QString& s);

protected:
    void configureUi();

private:
    AgateMedicationSPtr m_d;

    MoleculeManagementWidget* m_molecules;
    QGroupBox* m_details;
    QLineEdit* m_dosageInMgW;

    QDialogButtonBox* m_b;

    AgateMedication m_buffer;
};

