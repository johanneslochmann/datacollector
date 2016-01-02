#include "consultancyresultmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

ConsultancyResultManagementWidget::ConsultancyResultManagementWidget(QWidget* p)
    : TableManagementWidget(p, "forensics.consultancy_result", QObject::tr("Consultancy Result"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

