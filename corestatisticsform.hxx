#pragma once

#include <QWidget>

#include <memory>

#include <QSqlQuery>
#include <QSqlQueryModel>

#include "sqltablemodel.hxx"

namespace Ui {
class CoreStatisticsForm;
}

class CoreStatisticsForm : public QWidget
{
    Q_OBJECT

public:
    explicit CoreStatisticsForm(QWidget *parent = 0);
    ~CoreStatisticsForm();

public slots:
    void reloadStatistics();
    void reloadData();

protected:
    void onReportActivated(const QModelIndex &idx);

private:
    std::unique_ptr<Ui::CoreStatisticsForm> m_ui;

    SqlTableModel* m_sourcesM;
    SqlTableModel* m_reportM;

    QString m_currentReportName { "" };
};

