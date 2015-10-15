#include "probandmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"
#include "dateeditdelegate.hxx"

ProbandManagementWidget::ProbandManagementWidget(QWidget *p)
    : TableManagementWidget(p, tr("core.proband"), QObject::tr("Probands"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column
    view()->setItemDelegateForColumn(model()->fieldIndex("birthday"), new DateEditDelegate(view()));

    model()->select();
}

