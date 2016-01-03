#include "housingtypecombobox.hxx"

#include "datacollector.hxx"
#include "housingtypegateway.hxx"

#include <algorithm>

HousingTypeComboBox::HousingTypeComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &HousingTypeComboBox::onCurrentDatasetChanged);
    reload();
}

void HousingTypeComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentHousingTypeChanged(std::dynamic_pointer_cast<HousingType>(s));
}

StorableSPtr HousingTypeComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_housingTypes.begin(), m_housingTypes.end(), [=](HousingTypeSPtr cand) { return (cand->name() == txt); });

    if (m_housingTypes.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void HousingTypeComboBox::implReload()
{
    try {
        clear();
        m_housingTypes = HousingTypeGateway().loadAll();

        for (auto p : m_housingTypes) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load HousingType list"), this);
    }
}

