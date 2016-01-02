#include "weapontypemanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

WeaponTypeManagementWidget::WeaponTypeManagementWidget(QWidget *p)
    : TableManagementWidget(p, "forensics.weapon_type", QObject::tr("Weapon Types"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

