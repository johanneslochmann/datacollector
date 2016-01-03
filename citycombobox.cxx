#include "citycombobox.hxx"

#include "datacollector.hxx"
#include "citygateway.hxx"

#include <algorithm>

CityComboBox::CityComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &CityComboBox::onCurrentDatasetChanged);
    reload();
}

void CityComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentCityChanged(std::dynamic_pointer_cast<City>(s));
}

StorableSPtr CityComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_cities.begin(), m_cities.end(), [=](CitySPtr cand) { return (cand->name() == txt); });

    if (m_cities.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void CityComboBox::implReload()
{
    try {
        clear();
        m_cities = CityGateway().loadAll();

        for (auto p : m_cities) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load City list"), this);
    }
}

