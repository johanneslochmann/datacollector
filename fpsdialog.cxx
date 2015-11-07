#include "fpsdialog.hxx"
#include "ui_fpsdialog.h"

FPSDialog::FPSDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FPSDialog)
{
    ui->setupUi(this);
}

FPSDialog::~FPSDialog()
{
    delete ui;
}
