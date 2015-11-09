#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QCalendarWidget>

#include "sexcombobox.hxx"
#include "projectcombobox.hxx"
#include "campaigncombobox.hxx"

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

signals:

public slots:
    void accept();
    void reject();

    void onProjectChanged(ProjectSPtr p);
    void onCampaignChanged(CampaignSPtr c);
    void onSurveyDateChanged(const QDate& d);

protected:
    void configureUi();
    void configureSurveyBox();
    void configurePersonalBox();

private:
    AgateRecordSPtr m_r;
    QDialogButtonBox* m_b;

    QGroupBox* m_rootBox;

    QGroupBox* m_surveyBox;
    ProjectComboBox* m_projects;
    CampaignComboBox* m_campaigns;
    QCalendarWidget* m_surveyDate;

    QGroupBox* m_personalBox;
    SexComboBox* m_sexes;

    ProjectSPtr m_defaultProject;
    CampaignSPtr m_defaultCampaign;
    QDate m_defaultDate;
};
