#pragma once

#include <QComboBox>

#include "storable.hxx"

class DataComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit DataComboBox(QWidget* p);

signals:
    void datasetActivated(const StorableSPtr s);

public slots:
    void onItemActivated(const QString& txt);
    void reload() { implReload(); }

protected:
    virtual StorableSPtr storableForText(const QString& txt) const = 0;
    virtual void implReload() = 0;
};
