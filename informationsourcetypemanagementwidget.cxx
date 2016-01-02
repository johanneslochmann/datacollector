#include "informationsourcetypemanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

InformationSourceTypeManagementWidget::InformationSourceTypeManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.information_source_type", QObject::tr("Information Source Type"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Code"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

