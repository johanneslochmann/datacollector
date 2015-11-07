#pragma once

#include <QDialog>

#include <memory>

namespace Ui {
class CGIDialog;
}

class CGIDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CGIDialog(QWidget *parent = 0);
    ~CGIDialog();

    double severity() const { return m_severity; }
    double improvement() const { return m_improvement; }
    QString comment() const { return m_comment; }

public slots:
    void onSeverityChanged(const QString& d);
    void onImprovementChanged(const QString& d);
    void onCommentChanged();

private:
    std::unique_ptr<Ui::CGIDialog> ui;

    double m_severity { 0.0 };
    double m_improvement { 0.0 };
    QString m_comment { "" };
};

