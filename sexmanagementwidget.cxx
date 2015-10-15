#include "sexmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

SexManagementWidget::SexManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.sex", QObject::tr("Sex"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column
    model()->select();
}

