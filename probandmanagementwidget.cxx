#include "probandmanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "sqltablemodel.hxx"
#include "tableview.hxx"
#include "dateeditdelegate.hxx"

ProbandManagementWidget::ProbandManagementWidget(QWidget *p)
    : TableManagementWidget(p, tr("core.proband"), QObject::tr("Probands"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column
    model()->setRelation(model()->fieldIndex("sex_id"), QSqlRelation("core.sex", "id", "name"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));
    view()->setItemDelegateForColumn(model()->fieldIndex("birthday"), new DateEditDelegate(view()));

    model()->setHeaderData(model()->fieldIndex("external_id"), Qt::Horizontal, tr("External ID"));
    model()->setHeaderData(model()->fieldIndex("birthday"), Qt::Horizontal, tr("Birthday"));
    model()->setHeaderData(model()->fieldIndex("height_in_cm"), Qt::Horizontal, tr("Height [cm]"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Comment"));
    model()->setHeaderData(model()->fieldIndex("first_name"), Qt::Horizontal, tr("First Name"));
    model()->setHeaderData(model()->fieldIndex("surname"), Qt::Horizontal, tr("Surname"));
    model()->setHeaderData(model()->fieldIndex("year_of_birth"), Qt::Horizontal, tr("Year Of Birth"));
    model()->setHeaderData(4, Qt::Horizontal, tr("Sex"));

    model()->select();
}

