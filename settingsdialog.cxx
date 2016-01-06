#include "settingsdialog.hxx"

#include <QGridLayout>
#include <QGroupBox>
#include <QDialogButtonBox>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setLayout(new QVBoxLayout(this));

    m_gb = new QGroupBox(tr("Settings"), this);
    m_b = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, Qt::Horizontal, this);

    layout()->addWidget(m_gb);
    layout()->addWidget(m_b);

    connect(m_b, &QDialogButtonBox::accepted, this, &SettingsDialog::accept);
    connect(m_b, &QDialogButtonBox::rejected, this, &SettingsDialog::reject);
}
