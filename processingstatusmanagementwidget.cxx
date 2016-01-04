#include "processingstatusmanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "tableview.hxx"
#include "sqltablemodel.hxx"

ProcessingStatusManagementWidget::ProcessingStatusManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.processing_status", QObject::tr("Processing States"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}
