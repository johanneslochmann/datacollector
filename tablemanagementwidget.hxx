#pragma once

#include <qgroupbox.h>

#include <qitemselectionmodel.h>

class SqlTableModel;
class TableView;

class QPushButton;
class QDataWidgetMapper;

class TableManagementWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit TableManagementWidget(QWidget *parent, const QString& tableName, const QString &title);

signals:

public slots:
    void reload(bool askUser=false);
    void create();
    void abort();
    void remove();
    void save();

    void onRowsInserted(const QModelIndex & parent, int first, int last);

protected:
    SqlTableModel* model() const { return m_model; }
    TableView* view() const { return m_view; }

    virtual const QString nameColumnName() const { return "name"; }

private:
    SqlTableModel* m_model;
    TableView* m_view;
    QDataWidgetMapper* m_mapper;

    QPushButton* m_create;
    QPushButton* m_delete;

    QPushButton* m_reload;
    QPushButton* m_save;
    QPushButton* m_abort;
};

