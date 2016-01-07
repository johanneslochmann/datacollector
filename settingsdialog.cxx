#include "settingsdialog.hxx"

#include <QGridLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QMessageBox>
#include <QComboBox>

#include "settings.hxx"
#include "datacollector.hxx"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setLayout(new QVBoxLayout(this));

    m_gb = new QGroupBox(tr("Settings"), this);
    auto m_l = new QFormLayout(m_gb);
    m_gb->setLayout(m_l);

    m_locales = new QComboBox(m_gb);
    QStringList locales;
    locales << "de_DE" << "it_IT" << "";
    m_locales->addItems(locales);
    m_locales->setCurrentText("");
    auto currLocal = Settings().loadLocale();

    if (locales.contains(currLocal)) {
        m_locales->setCurrentText(currLocal);
    } else {
        m_locales->setCurrentText("");
    }

    m_l->addRow(tr("&Locale"), m_locales);
    m_b = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, Qt::Horizontal, this);

    layout()->addWidget(m_gb);
    layout()->addWidget(m_b);

    connect(m_b, &QDialogButtonBox::accepted, this, &SettingsDialog::accept);
    connect(m_b, &QDialogButtonBox::rejected, this, &SettingsDialog::reject);
}

void SettingsDialog::accept()
{
    Settings().saveLocale(m_locales->currentText());

    DataCollector::get()->reloadTranslation();

    QMessageBox::information(this, tr("Information"), tr("You need to restart the application for the changes to have effect."));

    done(QDialog::Accepted);
}
