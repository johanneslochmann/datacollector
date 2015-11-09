#include "sexcombobox.hxx"

#include "datacollector.hxx"
#include "sexdatagateway.hxx"

#include <algorithm>

SexComboBox::SexComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &SexComboBox::onCurrentDatasetChanged);
    reload();
}

void SexComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentSexChanged(std::dynamic_pointer_cast<Sex>(s));
}

StorableSPtr SexComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_Sexs.begin(), m_Sexs.end(), [=](SexSPtr cand) { return (cand->name() == txt); });

    if (m_Sexs.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void SexComboBox::implReload()
{
    try {
        clear();
        m_Sexs = SexDataGateway().loadAll();

        for (auto p : m_Sexs) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Sex list"), this);
    }
}

