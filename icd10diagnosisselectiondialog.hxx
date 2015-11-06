#pragma once

#include <QDialog>

#include <QSqlQuery>
#include <QSqlQueryModel>

#include <memory>

namespace Ui {
class Icd10DiagnosisSelectionDialog;
}

class Icd10DiagnosisSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Icd10DiagnosisSelectionDialog(QWidget *parent = 0);
    ~Icd10DiagnosisSelectionDialog();

    int currentId() const { return m_selectedId; }
    QString comment() const { return m_comment; }

public slots:
    void onIndexActivated(const QModelIndex& idx);
    void onCommentChanged();

private:
    std::unique_ptr<Ui::Icd10DiagnosisSelectionDialog> ui;

    QSqlQuery m_q;
    QSqlQueryModel* m_m;

    int m_selectedId { 0 };
    QString m_comment { "" };
};
