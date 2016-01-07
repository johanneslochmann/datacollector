#pragma once

#include <QWidget>

#include <QLineEdit>
#include <QPushButton>

class FileNameSelector: public QWidget
{
    Q_OBJECT
public:
    explicit FileNameSelector(const QString& defaultValue, const QString& browserFilter, const QString& path, QWidget* p);

    QString value() const;

signals:
    void valueChanged(const QString& v);

public slots:
    void setValue(const QString& v);

protected slots:
    void browse();

private:
    QLineEdit* m_display;
    QPushButton* m_browse;
    QPushButton* m_clear;

    QString m_browserFilter;
    QString m_path;
};

