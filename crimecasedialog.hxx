#pragma once

#include <QDialog>

#include "crimecase.hxx"

class QGroupBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QTextEdit;

class HousingTypeComboBox;

class CrimeCaseDialog : public QDialog
{
    Q_OBJECT
public:
    CrimeCaseDialog(QWidget* p, CrimeCaseSPtr d);
    virtual ~CrimeCaseDialog();

public slots:
    void accept();

private:
    void createWidgets();
    void createCoreInfoBox();

    CrimeCaseSPtr m_crimeCase;
    QGroupBox* m_mainBox;

    QGroupBox* m_coreInfoBox;
    QLineEdit* m_name;
    HousingTypeComboBox* m_housingType;
    QLineEdit* m_crimeYear;
    QLineEdit* m_crimeDate;
    QLineEdit* m_crimeTime;
    QTextEdit* m_description;

    QDialogButtonBox* m_buttons;
};
