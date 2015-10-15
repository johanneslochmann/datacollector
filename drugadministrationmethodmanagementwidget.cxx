#include "drugadministrationmethodmanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "tableview.hxx"
#include "sqltablemodel.hxx"

DrugAdministrationMethodManagementWidget::DrugAdministrationMethodManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.administration_method", QObject::tr("Drug Administration Methods"))
{
    setWindowTitle(tr("Drug Administration Methods"));

    model()->setRelation(model()->fieldIndex("channel_into_patient_id"),
                         QSqlRelation("core.channel_into_patient", "id", "name"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->select();
}

