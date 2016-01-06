#include "cgidialog.hxx"
#include "ui_cgidialog.h"

#include <QLineEdit>
#include <QPlainTextEdit>

CGIDialog::CGIDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::unique_ptr<Ui::CGIDialog>(new Ui::CGIDialog))
{
    ui->setupUi(this);

    connect(ui->severity, &QLineEdit::textChanged, this, &CGIDialog::onSeverityChanged);
    connect(ui->improvement, &QLineEdit::textChanged, this, &CGIDialog::onImprovementChanged);
    connect(ui->comment, &QPlainTextEdit::textChanged, this, &CGIDialog::onCommentChanged);
}

CGIDialog::~CGIDialog()
{
}

void CGIDialog::onSeverityChanged(const QString &d)
{
    m_severity = d.toDouble();
}

void CGIDialog::onImprovementChanged(const QString &d)
{
    m_improvement = d.toDouble();
}

void CGIDialog::onCommentChanged()
{
    m_comment = ui->comment->toPlainText();
}
