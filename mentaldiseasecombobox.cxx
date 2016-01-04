#include "mentaldiseasecombobox.hxx"

#include "datacollector.hxx"
#include "mentaldiseasegateway.hxx"

#include <algorithm>

MentalDiseaseComboBox::MentalDiseaseComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &MentalDiseaseComboBox::onCurrentDatasetChanged);
    reload();
}

void MentalDiseaseComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentMentalDiseaseChanged(std::dynamic_pointer_cast<MentalDisease>(s));
}

StorableSPtr MentalDiseaseComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_MentalDiseases.begin(), m_MentalDiseases.end(), [=](MentalDiseaseSPtr cand) { return (cand->name() == txt); });

    if (m_MentalDiseases.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void MentalDiseaseComboBox::implReload()
{
    try {
        clear();
        m_MentalDiseases = MentalDiseaseGateway().loadAll();

        for (auto p : m_MentalDiseases) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load MentalDisease list"), this);
    }
}

