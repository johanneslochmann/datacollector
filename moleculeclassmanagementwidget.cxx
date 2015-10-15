#include "moleculeclassmanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

MoleculeClassManagementWidget::MoleculeClassManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.molecule_class", QObject::tr("Molecule Class"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column
    model()->select();
}

