#include "citymanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "tableview.hxx"
#include "sqltablemodel.hxx"

CityManagementWidget::CityManagementWidget(QWidget* p)
    : TableManagementWidget(p, "geo.city", QObject::tr("Cities"))
{
    setWindowTitle(tr("Cities"));

    model()->setRelation(model()->fieldIndex("country_id"), QSqlRelation("geo.country", "id", "name"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("people_count"), Qt::Horizontal, tr("# of Inhabitants"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));
    model()->setHeaderData(4, Qt::Horizontal, tr("Country"));

    model()->select();
}

