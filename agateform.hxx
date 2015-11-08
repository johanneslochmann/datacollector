#ifndef AGATEFORM_HXX
#define AGATEFORM_HXX

#include <QWidget>

namespace Ui {
class AgateForm;
}

class AgateForm : public QWidget
{
    Q_OBJECT

public:
    explicit AgateForm(QWidget *parent = 0);
    ~AgateForm();

private:
    Ui::AgateForm *ui;
};

#endif // AGATEFORM_HXX
