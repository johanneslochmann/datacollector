#include "projectmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

ProjectManagementWidget::ProjectManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.project", QObject::tr("Projects"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}


