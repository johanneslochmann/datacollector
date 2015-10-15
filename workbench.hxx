#pragma once

#include <QMdiArea>
#include <QStackedWidget>

class TableManagementWidget;

class Workbench : public QStackedWidget
{
    Q_OBJECT
public:
    explicit Workbench(QWidget *parent = 0);

signals:

public slots:
    void manageChannelsIntoPatient();
    void manageDrugAdministrationMethods();
    void manageMoleculeClasses();

private:
    TableManagementWidget* m_channelIntoPatient { nullptr };
    TableManagementWidget* m_drugAdministrationMethod { nullptr };
    TableManagementWidget* m_moleculeClass { nullptr };
};
