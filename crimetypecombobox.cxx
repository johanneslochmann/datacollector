#include "crimetypecombobox.hxx"

#include "datacollector.hxx"
#include "crimetypegateway.hxx"

#include <algorithm>

CrimeTypeComboBox::CrimeTypeComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &CrimeTypeComboBox::onCurrentDatasetChanged);
    reload();
}

void CrimeTypeComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentCrimeTypeChanged(std::dynamic_pointer_cast<CrimeType>(s));
}

StorableSPtr CrimeTypeComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_cities.begin(), m_cities.end(), [=](CrimeTypeSPtr cand) { return (cand->name() == txt); });

    if (m_cities.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void CrimeTypeComboBox::implReload()
{
    try {
        clear();
        m_cities = CrimeTypeGateway().loadAll();

        for (auto p : m_cities) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Crime Type list"), this);
    }
}

