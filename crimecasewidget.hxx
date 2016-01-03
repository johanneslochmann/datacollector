#pragma once

#include <QWidget>

class CrimeCasesTableWidget;
class QPushButton;

class CrimeCaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CrimeCaseWidget(QWidget *parent = 0);

signals:

public slots:
    void createCase();

private:
    void createCrimeCasesBox();

    CrimeCasesTableWidget* m_cases;
    QPushButton* m_reloadCases;
    QPushButton* m_createCase;
    QPushButton* m_editCase;
    QPushButton* m_deleteCase;
};
