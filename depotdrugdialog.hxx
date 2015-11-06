#pragma once

#include <QDialog>

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

#include <memory>

namespace Ui {
class DepotDrugDialog;
}

class DepotDrugDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DepotDrugDialog(QWidget *parent = 0);
    ~DepotDrugDialog();

    int currentId() const { return m_selectedId; }
    double dosage() const { return m_dosage; }
    QDate lastInjectionDate() const { return m_lastInjectionDate; }
    int interval() const { return m_injectionInterval; }
    QString comment() const { return m_comment; }

public slots:
    void onIndexActivated(const QModelIndex& idx);
    void onLastInjectionDateChanged(const QDate& d);
    void onDosageChanged(const QString& s);
    void onInjectionIntervalChanged(const QString& s);
    void onCommentChanged();

private:
    std::unique_ptr<Ui::DepotDrugDialog> ui;

    QSqlQuery m_q;
    QSqlQueryModel* m_m;

    int m_selectedId { 0 };
    QDate m_lastInjectionDate { QDate() };
    double m_dosage { 0.0 };
    int m_injectionInterval { 0 };
    QString m_comment { "" };
};

