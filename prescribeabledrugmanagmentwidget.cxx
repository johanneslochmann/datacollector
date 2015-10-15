#include "prescribeabledrugmanagmentwidget.hxx"

#include <QSqlRelationalDelegate>

#include "sqltablemodel.hxx"
#include "tableview.hxx"

PrescribeableDrugManagmentWidget::PrescribeableDrugManagmentWidget(QWidget *p)
    : TableManagementWidget(p, "core.prescribeable_drug", QObject::tr("Prescribeable Drug"))
{
    model()->setRelation(model()->fieldIndex("drug_id"), QSqlRelation("core.drug", "id", "name"));
    model()->setRelation(model()->fieldIndex("dosage_unit_id"), QSqlRelation("core.unit", "id", "name"));
    model()->setRelation(model()->fieldIndex("administration_method_id"), QSqlRelation("core.administration_method", "id", "name"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));

    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->select();
}
