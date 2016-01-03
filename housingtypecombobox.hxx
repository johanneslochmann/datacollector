#pragma once

#include "datacombobox.hxx"

#include "housingtype.hxx"

class HousingTypeComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit HousingTypeComboBox(QWidget* p);

signals:
    void currentHousingTypeChanged(HousingTypeSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    HousingTypeSPtrVector m_housingTypes;
};
