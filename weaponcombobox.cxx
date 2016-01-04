#include "weaponcombobox.hxx"

#include "datacollector.hxx"
#include "weapongateway.hxx"

#include <algorithm>

WeaponComboBox::WeaponComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &WeaponComboBox::onCurrentDatasetChanged);
    reload();
}

void WeaponComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentWeaponChanged(std::dynamic_pointer_cast<Weapon>(s));
}

StorableSPtr WeaponComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_Weapons.begin(), m_Weapons.end(), [=](WeaponSPtr cand) { return (cand->name() == txt); });

    if (m_Weapons.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void WeaponComboBox::implReload()
{
    try {
        clear();
        m_Weapons = WeaponGateway().loadAll();

        for (auto p : m_Weapons) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Weapon list"), this);
    }
}

