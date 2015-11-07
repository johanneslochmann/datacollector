#pragma once

#include <QDialog>

#include <memory>

namespace Ui {
class GAFDialog;
}

class GAFDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GAFDialog(QWidget *parent = 0);
    ~GAFDialog();

    double value() const { return m_value; }
    QString description() const { return m_description; }

public slots:
    void onValueChanged(const QString& v);
    void onDescriptionChanged();

private:
    std::unique_ptr<Ui::GAFDialog> ui;

    double m_value { 0.0 };
    QString m_description { "" };
};

