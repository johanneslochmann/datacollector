#include "sexmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

SexManagementWidget::SexManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.sex", QObject::tr("Sex"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

