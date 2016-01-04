#include "informationsourcetypecombobox.hxx"

#include "datacollector.hxx"
#include "informationsourcetypegateway.hxx"

#include <algorithm>

InformationSourceTypeComboBox::InformationSourceTypeComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &InformationSourceTypeComboBox::onCurrentDatasetChanged);
    reload();
}

void InformationSourceTypeComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentInformationSourceTypeChanged(std::dynamic_pointer_cast<InformationSourceType>(s));
}

StorableSPtr InformationSourceTypeComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_informationSourceTypes.begin(), m_informationSourceTypes.end(), [=](InformationSourceTypeSPtr cand) { return (cand->name() == txt); });

    if (m_informationSourceTypes.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void InformationSourceTypeComboBox::implReload()
{
    try {
        clear();
        m_informationSourceTypes = InformationSourceTypeGateway().loadAll();

        for (auto p : m_informationSourceTypes) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load InformationSourceType list"), this);
    }
}

