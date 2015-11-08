#include "agateform.hxx"
#include "ui_agateform.h"

AgateForm::AgateForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AgateForm)
{
    ui->setupUi(this);
}

AgateForm::~AgateForm()
{
    delete ui;
}
