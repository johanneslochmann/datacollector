#pragma once

#include <QDialog>

#include <QSqlQuery>
#include <QSqlQueryModel>

#include <memory>

namespace Ui {
class CollateralEffectDialog;
}

class CollateralEffectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CollateralEffectDialog(QWidget *parent = 0);
    ~CollateralEffectDialog();

    int currentId() const { return m_selectedId; }
    QString comment() const { return m_comment; }

public slots:
    void onIndexActivated(const QModelIndex& idx);
    void onCommentChanged();

private:
    std::unique_ptr<Ui::CollateralEffectDialog> ui;

    int m_selectedId { 0 };
    QString m_comment { "" };

    QSqlQuery m_q;
    QSqlQueryModel* m_m;
};


