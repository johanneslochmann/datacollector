#include "corestatisticsform.hxx"

#include "ui_corestatisticsform.h"

#include <QTableView>
#include <QDebug>

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
}

CoreStatisticsForm::~CoreStatisticsForm()
{
}

void CoreStatisticsForm::onReportActivated(const QModelIndex& idx)
{
    auto nameIdx = m_ui->m_reportSelector->model()->index(idx.row(), 0);

    auto currentReportName = m_ui->m_reportSelector->model()->data(nameIdx).toString();

    qDebug() << "request for report: " << currentReportName;

    m_reportM->setTable(currentReportName);;
    m_reportM->select();
}
