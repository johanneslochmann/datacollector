#include "modusoperandicombobox.hxx"

#include "datacollector.hxx"
#include "modusoperandigateway.hxx"

#include <algorithm>

ModusOperandiComboBox::ModusOperandiComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &ModusOperandiComboBox::onCurrentDatasetChanged);
    reload();
}

void ModusOperandiComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentModusOperandiChanged(std::dynamic_pointer_cast<ModusOperandi>(s));
}

StorableSPtr ModusOperandiComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_ModusOperandis.begin(), m_ModusOperandis.end(), [=](ModusOperandiSPtr cand) { return (cand->name() == txt); });

    if (m_ModusOperandis.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void ModusOperandiComboBox::implReload()
{
    try {
        clear();
        m_ModusOperandis = ModusOperandiGateway().loadAll();

        for (auto p : m_ModusOperandis) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load ModusOperandi list"), this);
    }
}

