#include "fpsdialog.hxx"
#include "ui_fpsdialog.h"

#include <QLineEdit>
#include <QTextEdit>

FPSDialog::FPSDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FPSDialog)
{
    ui->setupUi(this);

    connect(ui->fps, &QLineEdit::textChanged, this, &FPSDialog::onValueChanged);
    connect(ui->comment, &QTextEdit::textChanged, this, &FPSDialog::onDescriptionChanged);
}

FPSDialog::~FPSDialog()
{
}

void FPSDialog::onValueChanged(const QString &v)
{
    m_value = v.toDouble();
}

void FPSDialog::onDescriptionChanged()
{
    m_description = ui->comment->toPlainText();
}
