#include "drugadministrationmethodmanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "tableview.hxx"
#include "sqltablemodel.hxx"

DrugAdministrationMethodManagementWidget::DrugAdministrationMethodManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.administration_method", QObject::tr("Drug Administration Methods"))
{
    setWindowTitle(tr("Drug Administration Methods"));

    model()->setRelation(model()->fieldIndex("channel_into_patient_id"), QSqlRelation("core.channel_into_patient", "id", "name"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));
    model()->setHeaderData(3, Qt::Horizontal, tr("Channel Into Patient"));

    model()->select();
}

