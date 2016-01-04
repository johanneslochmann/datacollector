#pragma once

#include <QDialog>

#include "informationsourceforcrimecase.hxx"

class InformationSourceForCrimeCaseDialog : public QDialog
{
public:
    InformationSourceForCrimeCaseDialog(QWidget* p, InformationSourceForCrimeCaseSPtr data);

private:
    InformationSourceForCrimeCaseSPtr m_data;
};
