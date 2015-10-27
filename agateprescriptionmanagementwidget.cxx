#include "agateprescriptionmanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "sqltablemodel.hxx"
#include "tableview.hxx"
#include "dateeditdelegate.hxx"

AgatePrescriptionManagementWidget::AgatePrescriptionManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.agate_prescription", QObject::tr("Agate Prescriptions"))
{
    model()->setRelation(model()->fieldIndex("survey_id"), QSqlRelation("core.survey", "id", "id"));
    model()->setRelation(model()->fieldIndex("prescription_type_id"), QSqlRelation("core.prescription_type", "id", "name"));
    model()->setRelation(model()->fieldIndex("prescribeable_drug_id"), QSqlRelation("core.prescribeable_drug", "id", "name"));
    model()->setRelation(model()->fieldIndex("dosage_unit_id"), QSqlRelation("core.unit", "id", "name"));

    view()->setItemDelegateForColumn(model()->fieldIndex("last_depot_injection_date"), new DateEditDelegate(view()));
    view()->setItemDelegate(new QSqlRelationalDelegate(view()));

    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->select();
}
