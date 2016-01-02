#include "housingtypemanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

HousingTypeManagementWidget::HousingTypeManagementWidget(QWidget* p)
    : TableManagementWidget(p, "geo.housing_type", QObject::tr("Housing Type"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

