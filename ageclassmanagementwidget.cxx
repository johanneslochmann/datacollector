#include "ageclassmanagementwidget.hxx"

#include "ageclassmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

AgeClassManagementWidget::AgeClassManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.age_class", QObject::tr("Age Classes"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("min_age"), Qt::Horizontal, tr("Min"));
    model()->setHeaderData(model()->fieldIndex("max_age"), Qt::Horizontal, tr("Max"));
    model()->setHeaderData(model()->fieldIndex("age_interval"), Qt::Horizontal, tr("Interval"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

