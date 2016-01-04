#include "crimecasecombobox.hxx"

#include "datacollector.hxx"
#include "crimecasegateway.hxx"

#include <algorithm>

CrimeCaseComboBox::CrimeCaseComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &CrimeCaseComboBox::onCurrentDatasetChanged);
    reload();
}

void CrimeCaseComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentCrimeCaseChanged(std::dynamic_pointer_cast<CrimeCase>(s));
}

StorableSPtr CrimeCaseComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_crimeCases.begin(), m_crimeCases.end(), [=](CrimeCaseSPtr cand) { return (cand->name() == txt); });

    if (m_crimeCases.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void CrimeCaseComboBox::implReload()
{
    try {
        clear();
        m_crimeCases = CrimeCaseGateway().loadAll();

        for (auto p : m_crimeCases) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load CrimeCase list"), this);
    }
}

