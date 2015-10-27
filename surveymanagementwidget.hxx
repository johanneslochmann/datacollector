#pragma once

#include "tablemanagementwidget.hxx"

class SurveyManagementWidget : public TableManagementWidget
{
    Q_OBJECT
public:
    explicit SurveyManagementWidget(QWidget* p);

signals:

public slots:

protected:
    const QString nameColumnName() const override { return "id"; }
};
