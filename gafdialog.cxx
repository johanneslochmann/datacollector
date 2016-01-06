#include "gafdialog.hxx"
#include "ui_gafdialog.h"

#include <QLineEdit>
#include <QPlainTextEdit>

GAFDialog::GAFDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GAFDialog)
{
    ui->setupUi(this);

    connect(ui->gaf, &QLineEdit::textChanged, this, &GAFDialog::onValueChanged);
    connect(ui->comment, &QPlainTextEdit::textChanged, this, &GAFDialog::onDescriptionChanged);
}

GAFDialog::~GAFDialog()
{
}

void GAFDialog::onValueChanged(const QString &v)
{
    m_value = v.toDouble();
}

void GAFDialog::onDescriptionChanged()
{
    m_description = ui->comment->toPlainText();
}
