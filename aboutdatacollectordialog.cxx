#include "aboutdatacollectordialog.hxx"
#include "ui_aboutdatacollectordialog.h"

#include <QGuiApplication>

AboutDataCollectorDialog::AboutDataCollectorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDataCollectorDialog)
{
    ui->setupUi(this);

    ui->m_infoL->setText(tr("<p><b>This is %1.</b></p>"
                            "<p><a href=\"mailto:johannes.lochmann@gmail.com\">johannes.lochmann@gmail.com</a></p>")
                         .arg(QGuiApplication::applicationDisplayName()));
}

AboutDataCollectorDialog::~AboutDataCollectorDialog()
{
    delete ui;
}
