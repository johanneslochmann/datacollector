#pragma once

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <memory>

namespace Ui {
class OnDemandDrugDialog;
}

class OnDemandDrugDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnDemandDrugDialog(QWidget *parent = 0);
    ~OnDemandDrugDialog();

    int currentId() const { return m_selectedId; }

public slots:
    void onIndexActivated(const QModelIndex& idx);

private:
    std::unique_ptr<Ui::OnDemandDrugDialog> ui;

    QSqlQuery m_q;
    QSqlQueryModel* m_m;

    int m_selectedId { 0 };
};

