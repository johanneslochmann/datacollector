#ifndef FPSDIALOG_HXX
#define FPSDIALOG_HXX

#include <QDialog>

namespace Ui {
class FPSDialog;
}

class FPSDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FPSDialog(QWidget *parent = 0);
    ~FPSDialog();

private:
    Ui::FPSDialog *ui;
};

#endif // FPSDIALOG_HXX
