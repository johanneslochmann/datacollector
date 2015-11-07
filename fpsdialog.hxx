#pragma once

#include <QDialog>

#include <memory>

namespace Ui {
class FPSDialog;
}

class FPSDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FPSDialog(QWidget *parent = 0);
    ~FPSDialog();

    double value() const { return m_value; }
    QString description() const { return m_description; }

public slots:
    void onValueChanged(const QString& v);
    void onDescriptionChanged();

private:
    std::unique_ptr<Ui::FPSDialog> ui;

    double m_value { 0.0 };
    QString m_description { "" };
};

