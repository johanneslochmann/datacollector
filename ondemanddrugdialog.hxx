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
    QString comment() const { return m_comment; }

public slots:
    void onIndexActivated(const QModelIndex& idx);
    void onCommentChanged();

private:
    std::unique_ptr<Ui::OnDemandDrugDialog> ui;

    QSqlQuery m_q;
    QSqlQueryModel* m_m;

    int m_selectedId { 0 };
    QString m_comment { "" };
};

