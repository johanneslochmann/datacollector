#include "crimecaseparticipanttablewidget.hxx"

#include <QStringList>
#include <QDebug>
#include <QMessageBox>

#include "datacollector.hxx"

#include "crimecasegateway.hxx"

CrimeCaseParticipantTableWidget::CrimeCaseParticipantTableWidget(QWidget *p)
    : DataTableWidget(p)
{
    m_headerLabels << tr("Campaign") << tr("Proband") << tr("Survey Date") << tr("Organization") << tr("ID");

    connect(this, &DataTableWidget::currentItemChanged, this, &CrimeCaseParticipantTableWidget::onActivated);
}

void CrimeCaseParticipantTableWidget::onCrimeCaseChanged(CrimeCaseSPtr c)
{
    m_crimeCase = c;
    reload();
}

void CrimeCaseParticipantTableWidget::reload()
{
    clear();
/*
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
        setItem(r, m_campaignCol, new QTableWidgetItem(format(i->campaign())));
        setItem(r, m_probandCol, new QTableWidgetItem(format(i->proband())));
        setItem(r, m_surveyDateCol, new QTableWidgetItem(i->survey()->date().toString("dd.MM.yyyy")));
        setItem(r, m_organizationCol, new QTableWidgetItem(format(i->organization())));
        setItem(r, m_idCol, new QTableWidgetItem(QString("%1").arg(i->survey()->id())));

        r++;
    }
    */
}

void CrimeCaseParticipantTableWidget::editSelected()
{

}

void CrimeCaseParticipantTableWidget::deleteSelected()
{
    auto itm = currentItem();

    if (!itm) {
        return;
    }

    auto idItm = item(itm->row(), m_idCol);

    if (!idItm) {
        return;
    }
/*
    if (QMessageBox::Yes != QMessageBox::warning(this,
                                                 tr("Delete Survey?"),
                                                 tr("<p>Delete Survey %1?</p>")
                                                 .arg(idItm->data(Qt::DisplayRole).toInt()),
                                                 QMessageBox::Yes | QMessageBox::No)) {
        return;
    }

    AgateRecordGateway().remove(idItm->data(Qt::DisplayRole).toInt());
    reload();
    */
}

void CrimeCaseParticipantTableWidget::onActivated(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    (void) previous;

    if (!currentItem()) {
        emit crimeCaseParticipantActivated(0);
        return;
    }

    auto idItm = item(current->row(), m_idCol);

    if (!idItm) {
        emit crimeCaseParticipantActivated(0);
        return;
    }

    emit crimeCaseParticipantActivated(idItm->data(Qt::DisplayRole).toInt());
}

