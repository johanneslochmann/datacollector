#pragma once

#include <QDialog>

#include <memory>

namespace Ui {
class WHOQOLDialog;
}

class WHOQOLDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WHOQOLDialog(QWidget *parent = 0);
    ~WHOQOLDialog();

    double physical() const { return m_physical; }
    double psychological() const { return m_psychological; }
    double social() const { return m_social; }
    double environmental() const { return m_environmental; }

    QString description() const { return m_description; }

public slots:
    void onPhysicalChanged(const QString& v);
    void onPsychologicalChanged(const QString& v);
    void onSocialChanged(const QString& v);
    void onEnvironmentalChanged(const QString& v);
    void onDescriptionChanged();

private:
    std::unique_ptr<Ui::WHOQOLDialog> ui;

    double m_physical { 0.0 };
    double m_psychological { 0.0 };
    double m_social { 0.0 };
    double m_environmental { 0.0 };
    QString m_description { "" };
};

