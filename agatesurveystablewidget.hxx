#pragma once

#include <datatablewidget.hxx>

#include "project.hxx"
#include "campaign.hxx"
#include "proband.hxx"
#include "organization.hxx"

class AgateSurveysTableWidget : public DataTableWidget
{
    Q_OBJECT
public:
    explicit AgateSurveysTableWidget(QWidget* p);

    int idColumn() const { return m_idCol; }

signals:

public slots:
    void onProjectChanged(ProjectSPtr p);
    void onCampaignChanged(CampaignSPtr c);
    void reload();
    void editSelected();
    void deleteSelected();

protected:
    QString format(CampaignSPtr c) const;
    QString format(ProbandSPtr c) const;
    QString format(OrganizationSPtr o) const;

private:
    ProjectSPtr m_project;
    CampaignSPtr m_campaign;

    QStringList m_headerLabels;
    int m_campaignCol { 0 };
    int m_probandCol { m_campaignCol + 1 };
    int m_surveyDateCol { m_probandCol + 1 };
    int m_organizationCol { m_surveyDateCol + 1 };
    int m_idCol { m_organizationCol + 1 };

};

