#include "campaignmanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "tableview.hxx"
#include "sqltablemodel.hxx"

CampaignManagementWidget::CampaignManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.campaign", QObject::tr("Campaigns"))
{
    model()->setRelation(model()->fieldIndex("project_id"),
                         QSqlRelation("core.project", "id", "name"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->select();
}
