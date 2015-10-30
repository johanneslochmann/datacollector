#pragma once

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <memory>

namespace Ui {
class DrugSelectionDialog;
}

class DrugSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrugSelectionDialog(QWidget *parent = 0);
    ~DrugSelectionDialog();

    int currentId() const { return m_selectedId; }

public slots:
    void onIndexActivated(const QModelIndex& idx);

private:
    std::unique_ptr<Ui::DrugSelectionDialog> ui;

    QSqlQuery m_q;
    QSqlQueryModel* m_m;

    int m_selectedId { 0 };
};

