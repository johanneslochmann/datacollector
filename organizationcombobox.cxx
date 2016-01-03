#include "organizationcombobox.hxx"

#include "datacollector.hxx"
#include "organizationgateway.hxx"

#include <algorithm>

OrganizationComboBox::OrganizationComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &OrganizationComboBox::onCurrentDatasetChanged);
    reload();
}

void OrganizationComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentOrganizationChanged(std::dynamic_pointer_cast<Organization>(s));
}

StorableSPtr OrganizationComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_organizations.begin(), m_organizations.end(), [=](OrganizationSPtr cand) { return (cand->name() == txt); });

    if (m_organizations.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void OrganizationComboBox::implReload()
{
    try {
        clear();
        m_organizations = OrganizationGateway().loadAll();

        for (auto p : m_organizations) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Organization list"), this);
    }
}

