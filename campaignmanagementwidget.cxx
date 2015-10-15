#include "campaignmanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "tableview.hxx"
#include "sqltablemodel.hxx"
#include "dateeditdelegate.hxx"

CampaignManagementWidget::CampaignManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.campaign", QObject::tr("Campaigns"))
{
    model()->setRelation(model()->fieldIndex("project_id"),
                         QSqlRelation("core.project", "id", "name"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));
    view()->setItemDelegateForColumn(model()->fieldIndex("start_date"), new DateEditDelegate(view()));
    view()->setItemDelegateForColumn(model()->fieldIndex("end_date"), new DateEditDelegate(view()));

    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->select();
}
