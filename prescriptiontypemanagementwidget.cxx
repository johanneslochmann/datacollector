#include "prescriptiontypemanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

PrescriptionTypeManagementWidget::PrescriptionTypeManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.prescription_type", QObject::tr("Prescription Type"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column
    model()->select();
}

