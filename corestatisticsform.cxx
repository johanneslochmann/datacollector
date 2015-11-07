#include "corestatisticsform.hxx"

#include "ui_corestatisticsform.h"

#include <QTableView>
#include <QPushButton>
#include <QMessageBox>

#include "datacollector.hxx"

CoreStatisticsForm::CoreStatisticsForm(QWidget *parent) :
    QWidget(parent),
    m_ui(std::unique_ptr<Ui::CoreStatisticsForm>(new Ui::CoreStatisticsForm))
{
    m_ui->setupUi(this);

    m_sourcesM = new SqlTableModel(this, "corestat.available_reports");
    m_reportM = new SqlTableModel(this, "");

    m_ui->m_reportSelector->setModel(m_sourcesM);
    m_ui->m_reportSelector->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->m_reportSelector->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->m_reportSelector->setSortingEnabled(true);

    m_ui->m_data->setModel(m_reportM);
    m_ui->m_data->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->m_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->m_data->setSortingEnabled(true);

    connect(m_ui->m_reportSelector, &QTableView::activated, this, &CoreStatisticsForm::onReportActivated);
    connect(m_ui->reloadStatistics, &QPushButton::clicked, this, &CoreStatisticsForm::reloadStatistics);
    connect(m_ui->reloadData, &QPushButton::clicked, this, &CoreStatisticsForm::reloadData);
}

CoreStatisticsForm::~CoreStatisticsForm()
{
}

void CoreStatisticsForm::reloadStatistics()
{
    if (!m_sourcesM->select()) {
        DataCollector::get()->showDatabaseError(DatabaseError(m_sourcesM->lastError()), tr("Failed to load available statistics"), this);
    }
}

void CoreStatisticsForm::reloadData()
{
    if (m_currentReportName.isEmpty()) {
        QMessageBox::information(this, tr("Usage Hint"), tr("No Report selected."));
        return;
    }

    m_reportM->setTable(m_currentReportName);

    if (!m_reportM->select()) {
        DataCollector::get()->showDatabaseError(DatabaseError(m_sourcesM->lastError()), tr("Failed to load statistics: %1").arg(m_currentReportName), this);
    }
}

void CoreStatisticsForm::onReportActivated(const QModelIndex& idx)
{
    auto nameIdx = m_ui->m_reportSelector->model()->index(idx.row(), 0);

    m_currentReportName = m_ui->m_reportSelector->model()->data(nameIdx).toString();

    reloadData();
}
