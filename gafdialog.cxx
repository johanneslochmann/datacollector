#include "gafdialog.hxx"
#include "ui_gafdialog.h"

GAFDialog::GAFDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GAFDialog)
{
    ui->setupUi(this);
}

GAFDialog::~GAFDialog()
{
    delete ui;
}
