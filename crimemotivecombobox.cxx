#include "crimemotivecombobox.hxx"

#include "datacollector.hxx"
#include "crimemotivegateway.hxx"

#include <algorithm>

CrimeMotiveComboBox::CrimeMotiveComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &CrimeMotiveComboBox::onCurrentDatasetChanged);
    reload();
}

void CrimeMotiveComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentCrimeMotiveChanged(std::dynamic_pointer_cast<CrimeMotive>(s));
}

StorableSPtr CrimeMotiveComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_cities.begin(), m_cities.end(), [=](CrimeMotiveSPtr cand) { return (cand->name() == txt); });

    if (m_cities.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void CrimeMotiveComboBox::implReload()
{
    try {
        clear();
        m_cities = CrimeMotiveGateway().loadAll();

        for (auto p : m_cities) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Crime Motive list"), this);
    }
}

