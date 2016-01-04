#pragma once

#include "datacombobox.hxx"

#include "crimetype.hxx"

class CrimeTypeComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit CrimeTypeComboBox(QWidget* p);

signals:
    void currentCrimeTypeChanged(CrimeTypeSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    CrimeTypeSPtrVector m_cities;
};
