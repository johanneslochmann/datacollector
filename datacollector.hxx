#pragma once

#include <QApplication>

class QAction;

class DataCollector : public QApplication
{
    Q_OBJECT
public:
    static DataCollector* get();

    explicit DataCollector(int& argc, char** argv);
    virtual ~DataCollector();

    QAction* quitAction() const { return m_quit; }
    QAction* openDatabaseAction() const { return m_openDatabase; }
    QAction* closeDatabaseAction() const { return m_closeDatabase; }
    QAction* pingDatabaseAction() const { return m_pingDatabase; }
    QAction* aboutProgramAction() const { return m_aboutProgram; }
    QAction* aboutQtAction() const { return m_aboutQt; }

signals:
    void databaseAvailable();
    void databaseUnavailable();

public slots:
    void openDatabase();
    void closeDatabase();
    void pingDatabase();
    void aboutProgram();

private:
    void initActions();

    QAction* m_quit;
    QAction* m_openDatabase;
    QAction* m_closeDatabase;
    QAction* m_pingDatabase;
    QAction* m_aboutProgram;
    QAction* m_aboutQt;
};
