#include "drugmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

DrugManagementWidget::DrugManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.drug", QObject::tr("Drugs"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column
    model()->select();
}

