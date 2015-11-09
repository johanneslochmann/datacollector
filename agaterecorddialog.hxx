#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QGroupBox>

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

signals:

public slots:
    void accept();
    void reject();

protected:
    void configureUi();
    void configureSurveyBox();
    void configurePersonalBox();

private:
    AgateRecordSPtr m_r;
    QDialogButtonBox* m_b;

    QGroupBox* m_rootBox;

    QGroupBox* m_surveyBox;
    QGroupBox* m_personalBox;
    ProjectComboBox* m_projects;
    CampaignComboBox* m_campaigns;
    SexComboBox* m_sexes;

    ProjectSPtr m_defaultProject;
    CampaignSPtr m_defaultCampaign;
};
