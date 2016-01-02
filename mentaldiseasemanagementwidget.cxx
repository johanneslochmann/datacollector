#include "mentaldiseasemanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

MentalDiseaseManagementWidget::MentalDiseaseManagementWidget(QWidget* p)
    : TableManagementWidget(p, "forensics.mental_disease", QObject::tr("Mental Disease"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

