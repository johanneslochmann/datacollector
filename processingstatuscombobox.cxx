#include "processingstatuscombobox.hxx"

#include "datacollector.hxx"
#include "processingstatusgateway.hxx"

#include <algorithm>

ProcessingStatusComboBox::ProcessingStatusComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &ProcessingStatusComboBox::onCurrentDatasetChanged);
    reload();
}

void ProcessingStatusComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentProcessingStatusChanged(std::dynamic_pointer_cast<ProcessingStatus>(s));
}

StorableSPtr ProcessingStatusComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_ProcessingStatuss.begin(), m_ProcessingStatuss.end(), [=](ProcessingStatusSPtr cand) { return (cand->name() == txt); });

    if (m_ProcessingStatuss.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void ProcessingStatusComboBox::implReload()
{
    try {
        clear();
        m_ProcessingStatuss = ProcessingStatusGateway().loadAll();

        for (auto p : m_ProcessingStatuss) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load ProcessingStatus list"), this);
    }
}

