#pragma once

#include <QMainWindow>

class Workbench;

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
};
