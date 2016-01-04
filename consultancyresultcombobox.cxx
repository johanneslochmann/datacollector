#include "consultancyresultcombobox.hxx"

#include "datacollector.hxx"
#include "consultancyresultgateway.hxx"

#include <algorithm>

ConsultancyResultComboBox::ConsultancyResultComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &ConsultancyResultComboBox::onCurrentDatasetChanged);
    reload();
}

void ConsultancyResultComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentConsultancyResultChanged(std::dynamic_pointer_cast<ConsultancyResult>(s));
}

StorableSPtr ConsultancyResultComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_cities.begin(), m_cities.end(), [=](ConsultancyResultSPtr cand) { return (cand->name() == txt); });

    if (m_cities.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void ConsultancyResultComboBox::implReload()
{
    try {
        clear();
        m_cities = ConsultancyResultGateway().loadAll();

        for (auto p : m_cities) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Consultancy Result list"), this);
    }
}

