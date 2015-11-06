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

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));
    model()->setHeaderData(3, Qt::Horizontal, tr("Molecule Class"));

    model()->select();
}
