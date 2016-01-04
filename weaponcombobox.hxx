#pragma once

#include "datacombobox.hxx"

#include "weapon.hxx"

class WeaponComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit WeaponComboBox(QWidget* p);

signals:
    void currentWeaponChanged(WeaponSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    WeaponSPtrVector m_Weapons;
};
