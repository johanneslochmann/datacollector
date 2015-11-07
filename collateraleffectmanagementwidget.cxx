#include "collateraleffectmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

CollateralEffectManagementWidget::CollateralEffectManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.collateral_effect", QObject::tr("Collateral Effects"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

