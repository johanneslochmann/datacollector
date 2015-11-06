#include "unitmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

UnitManagementWidget::UnitManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.unit", QObject::tr("Units"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

