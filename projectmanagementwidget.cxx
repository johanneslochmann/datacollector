#include "projectmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

ProjectManagementWidget::ProjectManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.project", QObject::tr("Projects"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column
    model()->select();
}

