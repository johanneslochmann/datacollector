#include "drugmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

DrugManagementWidget::DrugManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.drug", QObject::tr("Drugs"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

