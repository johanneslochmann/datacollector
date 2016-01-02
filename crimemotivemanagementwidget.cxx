#include "crimemotivemanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

CrimeMotiveManagementWidget::CrimeMotiveManagementWidget(QWidget* p)
    : TableManagementWidget(p, "forensics.crime_motive", QObject::tr("Crime Motive"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

