#include "icd10diagnosismanagementwidget.hxx"

#include "sqltablemodel.hxx"
#include "tableview.hxx"

Icd10DiagnosisManagementWidget::Icd10DiagnosisManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.icd10_diagnosis", QObject::tr("ICD Diagnosis"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column
    model()->select();
}

