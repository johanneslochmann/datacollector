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
    void manageMolecules();
    void manageSexes();
    void manageUnits();
    void manageProjects();

private:
    TableManagementWidget* m_channelIntoPatient;
    TableManagementWidget* m_drugAdministrationMethod;
    TableManagementWidget* m_moleculeClass;
    TableManagementWidget* m_molecules;
    TableManagementWidget* m_sexes;
    TableManagementWidget* m_units;
    TableManagementWidget* m_projects;
};
