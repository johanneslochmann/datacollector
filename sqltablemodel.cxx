#include "sqltablemodel.hxx"

#include "datacollector.hxx"

SqlTableModel::SqlTableModel(QObject *parent, const QString &tableName)
    : QSqlRelationalTableModel(parent, DataCollector::get()->database())
{
    setTable(tableName);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}
