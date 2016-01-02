#include "crimetypemanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

CrimeTypeManagementWidget::CrimeTypeManagementWidget(QWidget* p)
    : TableManagementWidget(p, "forensics.crime_type", QObject::tr("Crime Type"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

