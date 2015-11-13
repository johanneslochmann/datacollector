#pragma once

#include <QDialog>

#include <QPushButton>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QCalendarWidget>
#include <QLineEdit>

#include "sexcombobox.hxx"
#include "projectcombobox.hxx"
#include "campaigncombobox.hxx"
#include "organizationcombobox.hxx"
#include "agatedepottablewidget.hxx"
#include "agatemedicationtablewidget.hxx"
#include "agatediagnosistablewidget.hxx"

#include "agaterecord.hxx"

class AgateRecordDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AgateRecordDialog(QWidget* p);
    explicit AgateRecordDialog(QWidget* p, AgateRecordSPtr r);

    void setDefaultProject(ProjectSPtr p);
    void setDefaultCampaign(CampaignSPtr c);
    void setDefaultDate(const QDate& d);
    void setDefaultOrganization(OrganizationSPtr o);

signals:

public slots:
    void accept();
    void reject();

    void onProjectChanged(ProjectSPtr p);
    void onCampaignChanged(CampaignSPtr c);
    void onOrganizationChanged(OrganizationSPtr o);
    void onSurveyDateChanged(const QDate& d);
    void onBirthYearChanged(const QString& y);
    void onSexChanged(SexSPtr s);

protected:
    void configureUi();
    void configureSurveyBox();
    void configurePersonalBox();
    void configureDepotBox();
    void configureMedicationBox();
    void configureDiagnosisBox();

    bool validate();

private:
    AgateRecordSPtr m_r;
    QDialogButtonBox* m_b;

    QGroupBox* m_rootBox;

    QGroupBox* m_surveyBox;
    ProjectComboBox* m_projects;
    CampaignComboBox* m_campaigns;
    OrganizationComboBox* m_organizations;
    QCalendarWidget* m_surveyDate;

    QGroupBox* m_personalBox;
    QLineEdit* m_birthYear;
    SexComboBox* m_sexes;

    QGroupBox* m_depotBox;
    AgateDepotTableWidget* m_depots;
    QPushButton* m_addDepot;
    QPushButton* m_removeDepot;

    QGroupBox* m_medicationBox;
    AgateMedicationTableWidget* m_medications;
    QPushButton* m_addMedication;
    QPushButton* m_removeMedication;

    QGroupBox* m_diagnosisBox;
    AgateDiagnosisTableWidget* m_diagnosis;
    QPushButton* m_addDiagnosis;
    QPushButton* m_removeDiagnosis;

    ProjectSPtr m_defaultProject;
    CampaignSPtr m_defaultCampaign;
    OrganizationSPtr m_defaultOrganization;
    QDate m_defaultDate;
};
