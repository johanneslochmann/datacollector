#include "databaseconnectiondatadialog.hxx"

#include "ui_databaseconnectiondatadialog.h"

#include <QLineEdit>
#include <QIntValidator>

#include "settings.hxx"

DatabaseConnectionDataDialog::DatabaseConnectionDataDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(std::unique_ptr<Ui::DatabaseConnectionDataDialog>(new Ui::DatabaseConnectionDataDialog))
{
    m_ui->setupUi(this);
    m_ui->m_port->setValidator(new QIntValidator(this));

    connect(m_ui->m_host, &QLineEdit::textChanged, this, &DatabaseConnectionDataDialog::hostChanged);
    connect(m_ui->m_port, &QLineEdit::textChanged, this, &DatabaseConnectionDataDialog::portChanged);
    connect(m_ui->m_database, &QLineEdit::textChanged, this, &DatabaseConnectionDataDialog::databaseChanged);
    connect(m_ui->m_host, &QLineEdit::textChanged, this, &DatabaseConnectionDataDialog::hostChanged);
    connect(m_ui->m_port, &QLineEdit::textChanged, this, &DatabaseConnectionDataDialog::portChanged);

    loadData();
    showData();
}

DatabaseConnectionDataDialog::~DatabaseConnectionDataDialog()
{
}

void DatabaseConnectionDataDialog::hostChanged(const QString &txt)
{
    m_cd.setHost(txt);
}

void DatabaseConnectionDataDialog::portChanged(const QString &txt)
{
    m_cd.setPort(txt.toInt());
}

void DatabaseConnectionDataDialog::databaseChanged(const QString &txt)
{
    m_cd.setDatabase(txt);
}

void DatabaseConnectionDataDialog::userChanged(const QString &txt)
{
    m_cd.setUserName(txt);
}

void DatabaseConnectionDataDialog::passwordChanged(const QString &txt)
{
    m_cd.setPassword(txt);
}

void DatabaseConnectionDataDialog::accept()
{
    saveData();
    done(QDialog::Accepted);
}

void DatabaseConnectionDataDialog::showData()
{
    m_ui->m_host->setText(m_cd.host());
    m_ui->m_port->setText(QString("%1").arg(m_cd.port()));
    m_ui->m_database->setText(m_cd.database());
    m_ui->m_user->setText(m_cd.userName());

    m_ui->m_password->setFocus();
}

void DatabaseConnectionDataDialog::loadData()
{
    m_cd = Settings().loadDatabaseConnectionData();
}

void DatabaseConnectionDataDialog::saveData()
{
    Settings().save(m_cd);
}
