#include "settingsdialog.hxx"

#include <QGridLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QMessageBox>

#include "settings.hxx"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setLayout(new QVBoxLayout(this));

    m_gb = new QGroupBox(tr("Settings"), this);
    auto m_l = new QFormLayout(m_gb);
    m_gb->setLayout(m_l);

    m_translationFile = new FileNameSelector(Settings().translationFileName(), m_gb);
    m_l->addRow(tr("&Translation File"), m_translationFile);

    m_b = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, Qt::Horizontal, this);

    layout()->addWidget(m_gb);
    layout()->addWidget(m_b);

    connect(m_b, &QDialogButtonBox::accepted, this, &SettingsDialog::accept);
    connect(m_b, &QDialogButtonBox::rejected, this, &SettingsDialog::reject);
}

void SettingsDialog::accept()
{
    Settings().save(m_translationFile->value());

    QMessageBox::information(this, tr("Information"), tr("You need to restart the application for the changes to have effect."));

    done(QDialog::Accepted);
}
