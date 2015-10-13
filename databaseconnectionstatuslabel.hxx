#pragma once

#include <QLabel>

class DatabaseConnectionStatusLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DatabaseConnectionStatusLabel(QWidget* p = nullptr);

signals:

public slots:
    void databaseAvailable();
    void databaseUnavailable();
};

