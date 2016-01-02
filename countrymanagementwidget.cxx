#include "countrymanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

CountryManagementWidget::CountryManagementWidget(QWidget* p)
    : TableManagementWidget(p, "geo.country", QObject::tr("Country"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("symbol"), Qt::Horizontal, tr("Symbol"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

