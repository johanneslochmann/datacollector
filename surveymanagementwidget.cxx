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
    model()->setRelation(model()->fieldIndex("organization_unit_id"), QSqlRelation("core.organization_unit", "id", "name"));
    model()->setRelation(model()->fieldIndex("smoking_habit_id"), QSqlRelation("core.smoking_habit", "id", "name"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));
    view()->setItemDelegateForColumn(model()->fieldIndex("survey_date"), new DateEditDelegate(view()));

    model()->setHeaderData(model()->fieldIndex("ID"), Qt::Horizontal, tr("Survey ID"));
    model()->setHeaderData(1, Qt::Horizontal, tr("External Proband ID"));
    model()->setHeaderData(2, Qt::Horizontal, tr("Campaign"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));
    model()->setHeaderData(model()->fieldIndex("survey_date"), Qt::Horizontal, tr("Survey Date"));
    model()->setHeaderData(5, Qt::Horizontal, tr("Organization Unit"));
    model()->setHeaderData(6, Qt::Horizontal, tr("Smoking Habit"));

    model()->select();
}
