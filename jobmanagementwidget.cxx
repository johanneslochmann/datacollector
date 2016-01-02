#include "jobmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

JobManagementWidget::JobManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.job", QObject::tr("Job"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

