#include "icd10diagnosisinsurveymanagementwidget.hxx"

#include <QSqlRelationalDelegate>

#include "sqltablemodel.hxx"
#include "tableview.hxx"

Icd10DiagnosisInSurveyManagementWidget::Icd10DiagnosisInSurveyManagementWidget(QWidget* p)
    : TableManagementWidget(p, "core.icd10_survey", QObject::tr("ICD10 Diagnosis in Survey"))
{
    model()->setRelation(model()->fieldIndex("icd10_diagnosis_id"), QSqlRelation("core.icd10_diagnosis", "id", "name"));
    model()->setRelation(model()->fieldIndex("survey_id"), QSqlRelation("core.survey", "id", "id"));

    view()->setItemDelegate(new QSqlRelationalDelegate(view()));

    model()->select();
}
