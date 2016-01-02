#include "modusoperandimanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

ModusOperandiManagementWidget::ModusOperandiManagementWidget(QWidget* p)
    : TableManagementWidget(p, "forensics.modus_operandi", QObject::tr("Modus Operandi"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

