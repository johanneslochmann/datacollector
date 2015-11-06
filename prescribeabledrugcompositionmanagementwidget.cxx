#include "prescribeabledrugcompositionmanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "sqltablemodel.hxx"
#include "tableview.hxx"

PrescribeableDrugCompositionManagementWidget::PrescribeableDrugCompositionManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.prescribeable_drug_composition", QObject::tr("Prescribeable Drug Composition"))
{
    model()->setRelation(model()->fieldIndex("prescribeable_drug_id"), QSqlRelation("core.prescribeable_drug", "id", "name"));
    model()->setRelation(model()->fieldIndex("molecule_id"), QSqlRelation("core.molecule", "id", "name"));
    model()->setRelation(model()->fieldIndex("amount_unit_id"), QSqlRelation("core.unit", "id", "name"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));

    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(1, Qt::Horizontal, tr("Prescribeable Drug"));
    model()->setHeaderData(2, Qt::Horizontal, tr("Molecule"));
    model()->setHeaderData(model()->fieldIndex("amount"), Qt::Horizontal, tr("Amount"));
    model()->setHeaderData(4, Qt::Horizontal, tr("Amount Unit"));

    model()->select();
}

