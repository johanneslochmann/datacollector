#pragma once

#include <QDialog>

class QWidget;
class QDialogButtonBox;
class QPushButton;
class QLineEdit;
class QGroupBox;
class QGridLayout;

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = 0);

signals:

public slots:

private:
    QGroupBox* m_gb;
    QDialogButtonBox* m_b;
};
