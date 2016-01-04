#include "jobcombobox.hxx"

#include "datacollector.hxx"
#include "jobgateway.hxx"

#include <algorithm>

JobComboBox::JobComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &JobComboBox::onCurrentDatasetChanged);
    reload();
}

void JobComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentJobChanged(std::dynamic_pointer_cast<Job>(s));
}

StorableSPtr JobComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_jobs.begin(), m_jobs.end(), [=](JobSPtr cand) { return (cand->name() == txt); });

    if (m_jobs.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void JobComboBox::implReload()
{
    try {
        clear();
        m_jobs = JobGateway().loadAll();

        for (auto p : m_jobs) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Job list"), this);
    }
}

