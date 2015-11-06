#pragma once

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <memory>

namespace Ui {
class PlasmaticLevelDialog;
}

class PlasmaticLevelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlasmaticLevelDialog(QWidget *parent = 0);
    ~PlasmaticLevelDialog();

    int currentId() const { return m_selectedId; }
    double value() const { return m_value; }
    QString unitName() const { return m_unitName; }
    QString comment() const { return m_comment; }

public slots:
    void onIndexActivated(const QModelIndex& idx);
    void onUnitActivated(const QString& txt);
    void onValueChanged(const QString& txt);
    void onCommentChanged();

private:
    std::unique_ptr<Ui::PlasmaticLevelDialog> ui;

    double m_value { 0.0 };
    QString m_unitName { "ng/ml" };
    int m_selectedId { 0 };
    QString m_comment { "" };

    QSqlQuery m_moleculeQry;
    QSqlQuery m_unitQry;

    QSqlQueryModel* m_moleculeModel;
    QSqlQueryModel* m_unitModel;
};

