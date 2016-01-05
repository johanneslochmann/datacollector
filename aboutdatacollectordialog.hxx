#pragma once

#include <QDialog>

namespace Ui {
class AboutDataCollectorDialog;
}

class AboutDataCollectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDataCollectorDialog(QWidget *parent = 0);
    ~AboutDataCollectorDialog();

private:
    Ui::AboutDataCollectorDialog *ui;
};

