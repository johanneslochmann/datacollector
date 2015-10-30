#pragma once

#include <QDialog>

#include <memory>

#include "databaseconnectiondata.hxx"

namespace Ui {
class DatabaseConnectionDataDialog;
}

class DatabaseConnectionDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseConnectionDataDialog(QWidget *parent = 0);
    ~DatabaseConnectionDataDialog();

    DatabaseConnectionData connectionData() const { return m_cd; }

public slots:
    void hostChanged(const QString& txt);
    void portChanged(const QString& txt);
    void databaseChanged(const QString& txt);
    void userChanged(const QString& txt);
    void passwordChanged(const QString& txt);

    void accept() override;

private:
    void showData();
    void loadData();
    void saveData();

    std::unique_ptr<Ui::DatabaseConnectionDataDialog> m_ui;

    DatabaseConnectionData m_cd;
};
