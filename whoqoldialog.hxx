#ifndef WHOQOLDIALOG_HXX
#define WHOQOLDIALOG_HXX

#include <QDialog>

namespace Ui {
class WHOQOLDialog;
}

class WHOQOLDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WHOQOLDialog(QWidget *parent = 0);
    ~WHOQOLDialog();

private:
    Ui::WHOQOLDialog *ui;
};

#endif // WHOQOLDIALOG_HXX
