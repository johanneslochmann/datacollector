#include "smokinghabitsmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

SmokingHabitsManagementWidget::SmokingHabitsManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.smoking_habit", QObject::tr("Smoking Habits"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("max_cigarettes"), Qt::Horizontal, tr("Max Cigarettes"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

