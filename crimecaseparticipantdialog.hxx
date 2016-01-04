#pragma once

#include <QDialog>

#include "crimecaseparticipant.hxx"

class QDialogButtonBox;
class QLineEdit;
class QTextEdit;

class CrimeCaseComboBox;
class CrimeCasePartyRoleComboBox;
class SexComboBox;

class CrimeCaseParticipantDialog : public QDialog
{
    Q_OBJECT

public:
    CrimeCaseParticipantDialog(QWidget* p, CrimeCaseParticipantSPtr ccp);

public slots:
    void accept();

private:
    CrimeCaseParticipantSPtr m_participant;

    CrimeCaseComboBox* m_crimeCase;
    CrimeCasePartyRoleComboBox* m_role;
    SexComboBox* m_sex;
    QLineEdit* m_name;
    QLineEdit* m_ageInYears;
    QTextEdit* m_description;

    QDialogButtonBox* m_bb;
};
