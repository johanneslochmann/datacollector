#pragma once

#include "datacombobox.hxx"

#include "city.hxx"

class CityComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit CityComboBox(QWidget* p);

signals:
    void currentCityChanged(CitySPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    CitySPtrVector m_cities;
};
