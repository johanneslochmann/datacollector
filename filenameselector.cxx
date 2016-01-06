#include "filenameselector.hxx"

#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

FileNameSelector::FileNameSelector(const QString& fn, QWidget* p)
    : QWidget(p)
{
    setLayout(new QHBoxLayout(this));
    layout()->setContentsMargins(0, 0, 0, 0);
    m_display = new QLineEdit(fn, this);
    m_display->setReadOnly(true);
    m_clear = new QPushButton(tr("&Clear"), this);
    m_browse = new QPushButton("...", this);

    layout()->addWidget(m_display);
    layout()->addWidget(m_clear);
    layout()->addWidget(m_browse);

    connect(m_display, &QLineEdit::textChanged, this, &FileNameSelector::valueChanged);
    connect(m_browse, &QPushButton::clicked, this, &FileNameSelector::browse);
    connect(m_clear, &QPushButton::clicked, m_display, &QLineEdit::clear);
}

QString FileNameSelector::value() const
{
    return m_display->text();
}

void FileNameSelector::setValue(const QString &v)
{
    m_display->setText(v);
}

void FileNameSelector::browse()
{
    auto fn = QFileDialog::getOpenFileName(this, tr("select translation file"), QDir::currentPath(), tr("Translation Files (*.ts)"));

    if (fn.isEmpty()) {
        return;
    }

    setValue(fn);
}
