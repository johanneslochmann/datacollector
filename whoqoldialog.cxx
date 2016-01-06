#include "whoqoldialog.hxx"
#include "ui_whoqoldialog.h"

#include <QLineEdit>
#include <QPlainTextEdit>

WHOQOLDialog::WHOQOLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WHOQOLDialog)
{
    ui->setupUi(this);

    connect(ui->physical, &QLineEdit::textChanged, this, &WHOQOLDialog::onPhysicalChanged);
    connect(ui->psychological, &QLineEdit::textChanged, this, &WHOQOLDialog::onPsychologicalChanged);
    connect(ui->social, &QLineEdit::textChanged, this, &WHOQOLDialog::onSocialChanged);
    connect(ui->environmental, &QLineEdit::textChanged, this, &WHOQOLDialog::onEnvironmentalChanged);
    connect(ui->comment, &QPlainTextEdit::textChanged, this, &WHOQOLDialog::onDescriptionChanged);
}

WHOQOLDialog::~WHOQOLDialog()
{
}

void WHOQOLDialog::onPhysicalChanged(const QString &v)
{
    m_physical = v.toDouble();
}

void WHOQOLDialog::onPsychologicalChanged(const QString &v)
{
    m_psychological = v.toDouble();
}

void WHOQOLDialog::onSocialChanged(const QString &v)
{
    m_social = v.toDouble();
}

void WHOQOLDialog::onEnvironmentalChanged(const QString &v)
{
    m_environmental = v.toDouble();
}

void WHOQOLDialog::onDescriptionChanged()
{
    m_description = ui->comment->toPlainText();
}
