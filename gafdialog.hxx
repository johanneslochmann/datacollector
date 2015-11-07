#ifndef GAFDIALOG_HXX
#define GAFDIALOG_HXX

#include <QDialog>

namespace Ui {
class GAFDialog;
}

class GAFDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GAFDialog(QWidget *parent = 0);
    ~GAFDialog();

private:
    Ui::GAFDialog *ui;
};

#endif // GAFDIALOG_HXX
