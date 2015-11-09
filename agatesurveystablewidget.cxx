#include "agatesurveystablewidget.hxx"

#include <QStringList>
#include <QDebug>

#include "datacollector.hxx"
#include "agaterecordgateway.hxx"

AgateSurveysTableWidget::AgateSurveysTableWidget(QWidget *p)
    : DataTableWidget(p)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_headerLabels << tr("Campaign") << tr("Proband") << tr("Survey Date") << tr("Organization"), tr("ID");
}

void AgateSurveysTableWidget::onProjectChanged(ProjectSPtr p)
{
    m_project = p;
    m_campaign = std::make_shared<Campaign>();
    reload();
}

void AgateSurveysTableWidget::onCampaignChanged(CampaignSPtr c)
{
    m_campaign = c;
    reload();
}

void AgateSurveysTableWidget::reload()
{
    clear();

    AgateRecordSPtrVector buf;

    try {
        // if a campaign filter is set, use it and ignore project filter (campaign already is in current project)
        if (m_campaign && m_campaign->hasId()) {
            qDebug() << "reloading for campaign: " << m_campaign->name();
            buf = AgateRecordGateway().loadAllInCampaign(m_campaign);
        } else {
            if (m_project && m_project->hasId()) {
                qDebug() << "reloading for project: " << m_project->name();
                buf = AgateRecordGateway().loadAllInProject(m_project);
            }
        }
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load agate surveys."), this);
    }

    setRowCount(buf.size());
    setColumnCount(m_idCol + 1);

    setHorizontalHeaderLabels(m_headerLabels);;

    int r=0;

    for (auto i : buf) {
        auto campaign = new QTableWidgetItem(format(i->campaign()));
        auto proband = new QTableWidgetItem(format(i->proband()));
        auto surveyDate = new QTableWidgetItem(i->survey()->date().toString("dd.MM.yyyy"));
        auto organization = new QTableWidgetItem(format(i->organization()));
        auto id = new QTableWidgetItem(i->survey()->id());

        setItem(r, m_campaignCol, campaign);
        setItem(r, m_probandCol, proband);
        setItem(r, m_surveyDateCol, surveyDate);
        setItem(r, m_organizationCol, organization);
        setItem(r, m_idCol, id);

        r++;
    }
}

QString AgateSurveysTableWidget::format(CampaignSPtr c) const
{
    return c->name();
}

QString AgateSurveysTableWidget::format(ProbandSPtr c) const
{
    QStringList buf;

    if (!c->surname().isEmpty()) {
        buf.append(c->surname());
    }

    if (!c->firstName().isEmpty()) {
        buf.append(c->firstName());
    }

    if (c->birthday().isValid()) {
        buf.append(c->birthday().toString("dd.MM.yyyy"));
    }

    if (c->externalId() > 0) {
        buf.append(tr("Ext. ID: %1").arg(c->externalId()));
    }

    buf.append(QString("[%1]").arg(c->id()));

    return buf.join(", ");
}

QString AgateSurveysTableWidget::format(OrganizationSPtr o) const
{
    return o->name();
}

