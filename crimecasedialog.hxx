#pragma once

#include <QDialog>

#include "crimecase.hxx"

class QGroupBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QTextEdit;
class QPushButton;

class HousingTypeComboBox;
class CityComboBox;
class CrimeCaseParticipantTableWidget;
class InformationSourceForCrimeCaseTableWidget;
class ProcessingStatusComboBox;

class CrimeCaseDialog : public QDialog
{
    Q_OBJECT
public:
    CrimeCaseDialog(QWidget* p, CrimeCaseSPtr d);
    virtual ~CrimeCaseDialog();

signals:
    void crimeCaseSaved();

public slots:
    void accept();
    void save();

    void createParticipant();
    void createInformationSource();

    void onCrimeCaseSaved();

private:
    void createWidgets();
    void createCoreInfoBox();
    void createParticipantsBox();
    void createInformationSourcesBox();

    CrimeCaseSPtr m_crimeCase;
    QGroupBox* m_mainBox;

    QGroupBox* m_coreInfoBox;
    ProcessingStatusComboBox* m_processingStatus;
    QLineEdit* m_name;
    HousingTypeComboBox* m_housingType;
    CityComboBox* m_city;
    QLineEdit* m_crimeYear;
    QLineEdit* m_crimeDate;
    QLineEdit* m_crimeTime;
    QTextEdit* m_description;

    QGroupBox* m_participantsBox;
    CrimeCaseParticipantTableWidget* m_participants;
    QPushButton* m_reloadParticipants;
    QPushButton* m_createParticipant;
    QPushButton* m_editParticipant;
    QPushButton* m_deleteParticipant;

    QGroupBox* m_informationSourcesBox;
    InformationSourceForCrimeCaseTableWidget* m_informationSources;
    QPushButton* m_reloadInformationSources;
    QPushButton* m_createInformationSource;
    QPushButton* m_editInformationSource;
    QPushButton* m_deleteInformationSource;

    QDialogButtonBox* m_buttons;
};
