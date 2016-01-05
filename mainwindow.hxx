#pragma once

#include <QMainWindow>

class QMenu;

class Workbench;
class DataCollector;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void databaseAboutToClose();
    void databaseAvailable();
    void databaseUnavailable();

private:
    void initMenues();
    void initStatusBar();

    Workbench* m_wb { nullptr };
    QMenu* m_fileM;
    QMenu* m_databaseM;
    QMenu* m_adminM;
    QMenu* m_projectM;
    QMenu* m_pharmacologyM;
    QMenu* m_agateM;
    QMenu* m_criminologyM;
    QMenu* m_statisticsM;
    QMenu* m_helpM;

    void createFileMenu(DataCollector* app);
    void createDatabaseMenu(DataCollector* app);
    void createAdminMenu(DataCollector* app);
    void createProjectMenu(DataCollector* app);
    void createPharmacologyMenu(DataCollector* app);
    void createAgateMenu(DataCollector* app);
    void createCriminologyMenu(DataCollector* app);
    void createStatisticsMenu(DataCollector* app);
    void createHelpMenu(DataCollector* app);
};
