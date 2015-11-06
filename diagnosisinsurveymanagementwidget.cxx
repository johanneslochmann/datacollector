#include "diagnosisinsurveymanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "sqltablemodel.hxx"
#include "tableview.hxx"
#include "dateeditdelegate.hxx"

DiagnosisInSurveyManagementWidget::DiagnosisInSurveyManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.icd10_survey", QObject::tr("ICD 10 Diagnosis in Survey"))
{
    model()->setRelation(model()->fieldIndex("survey_id"), QSqlRelation("core.survey", "id", "id"));
    model()->setRelation(model()->fieldIndex("icd10_diagnosis_id"), QSqlRelation("core.icd10_diagnosis", "id", "name"));

    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(0, Qt::Horizontal, tr("ICD10 Diagnosis"));

    model()->select();
}
