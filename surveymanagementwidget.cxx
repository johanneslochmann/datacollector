#include "surveymanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "dateeditdelegate.hxx"
#include "sqltablemodel.hxx"
#include "tableview.hxx"

SurveyManagementWidget::SurveyManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.survey", QObject::tr("Survey Data"))
{
    model()->setRelation(model()->fieldIndex("proband_id"), QSqlRelation("core.proband", "id", "external_id"));
    model()->setRelation(model()->fieldIndex("campaign_id"), QSqlRelation("core.campaign", "id", "name"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));
    view()->setItemDelegateForColumn(model()->fieldIndex("survey_date"), new DateEditDelegate(view()));

    view()->hideColumn(model()->fieldIndex("id")); // hide id column
    model()->select();
}
