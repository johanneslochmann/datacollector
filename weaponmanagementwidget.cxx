#include "weaponmanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "tableview.hxx"
#include "sqltablemodel.hxx"

WeaponManagementWidget::WeaponManagementWidget(QWidget* p)
    : TableManagementWidget(p, "forensics.weapon", QObject::tr("Weapons"))
{
    model()->setRelation(model()->fieldIndex("weapon_type_id"),
                         QSqlRelation("forensics.weapon_type", "id", "name"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));
    model()->setHeaderData(3, Qt::Horizontal, tr("Weapon Type"));

    model()->select();
}
