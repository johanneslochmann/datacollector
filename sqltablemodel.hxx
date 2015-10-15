#pragma once

#include <QSqlRelationalTableModel>

class SqlTableModel : public QSqlRelationalTableModel
{
public:
    SqlTableModel(QObject* parent, const QString& tableName);

signals:

public slots:
};
