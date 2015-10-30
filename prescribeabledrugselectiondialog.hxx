#pragma once

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <memory>

namespace Ui {
class PrescribeableDrugSelectionDialog;
}

class PrescribeableDrugSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrescribeableDrugSelectionDialog(QWidget *parent = 0);
    ~PrescribeableDrugSelectionDialog();

    int currentId() const { return m_selectedId; }

    double morningDosage() const { return m_morningDosage; }
    double lunchDosage() const { return m_lunchDosage; }
    double noonDosage() const { return m_noonDosage; }
    double nightDosage() const { return m_nightDosage; }

public slots:
    void onIndexActivated(const QModelIndex& idx);

    void onMorningDosageChanged(const QString& s);
    void onLunchDosageChanged(const QString& s);
    void onNoonDosageChanged(const QString& s);
    void onNightDosageChanged(const QString& s);

private:
    std::unique_ptr<Ui::PrescribeableDrugSelectionDialog> ui;

    QSqlQuery m_q;
    QSqlQueryModel* m_m;

    int m_selectedId { 0 };
    double m_morningDosage { 0.0 };
    double m_lunchDosage { 0.0 };
    double m_noonDosage { 0.0 };
    double m_nightDosage { 0.0 };
};
