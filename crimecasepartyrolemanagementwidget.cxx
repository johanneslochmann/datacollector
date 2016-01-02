#include "crimecasepartyrolemanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

CrimeCasePartyRoleManagementWidget::CrimeCasePartyRoleManagementWidget(QWidget* p)
    : TableManagementWidget(p, "forensics.crime_case_party_role", QObject::tr("Crime Case Party Role"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

