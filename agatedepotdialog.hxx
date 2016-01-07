#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QDateEdit>

#include "agaterecord.hxx"

#include "prescribeabledrugmanagmentwidget.hxx"

class AgateDepotDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AgateDepotDialog(QWidget* p);
    explicit AgateDepotDialog(QWidget* p, AgateDepotSPtr d);

    AgateDepotSPtr depot() const { return m_d; }

signals:

public slots:
    void accept();
    void onLastInjectionDateChanged(const QDate& d);
    void onDosisChanged(const QString& s);
    void onIntervalChanged(const QString& i);

protected:
    void configureUi();

private:
    AgateDepotSPtr m_d;

    PrescribeableDrugManagmentWidget* m_prescribeableDrugs;
    QGroupBox* m_details;
    QDateEdit* m_lastInjectionW;
    QLineEdit* m_dosageInMgW;
    QLineEdit* m_intervalInDaysW;

    QDialogButtonBox* m_b;

    AgateDepot m_buffer;
};

