#include "moleculemanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "tableview.hxx"
#include "sqltablemodel.hxx"

MoleculeManagementWidget::MoleculeManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.molecule", QObject::tr("Molecules"))
{
    model()->setRelation(model()->fieldIndex("molecule_class_id"),
                         QSqlRelation("core.molecule_class", "id", "name"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->select();
}
