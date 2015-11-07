#include "whoqoldialog.hxx"
#include "ui_whoqoldialog.h"

WHOQOLDialog::WHOQOLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WHOQOLDialog)
{
    ui->setupUi(this);
}

WHOQOLDialog::~WHOQOLDialog()
{
    delete ui;
}
