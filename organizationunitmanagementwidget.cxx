#include "organizationunitmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

OrganizationUnitManagementWidget::OrganizationUnitManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.organization_unit", QObject::tr("Organization Units"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}
