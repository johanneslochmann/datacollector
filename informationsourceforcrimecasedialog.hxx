#pragma once

#include <QDialog>

#include "informationsourceforcrimecase.hxx"

class QDialogButtonBox;
class QLineEdit;
class QPlainTextEdit;
class QDateTimeEdit;

class CrimeCaseComboBox;
class InformationSourceTypeComboBox;

class InformationSourceForCrimeCaseDialog : public QDialog
{
public:
    InformationSourceForCrimeCaseDialog(QWidget* p, InformationSourceForCrimeCaseSPtr data);

public slots:
    void accept();

private:
    InformationSourceForCrimeCaseSPtr m_data;

    CrimeCaseComboBox* m_crimeCases;
    InformationSourceTypeComboBox* m_sourceTypes;
    QLineEdit* m_url;
    QDateTimeEdit* m_when;
    QPlainTextEdit* m_description;
    QDialogButtonBox* m_buttons;
};
