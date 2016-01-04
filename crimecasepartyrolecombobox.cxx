#include "crimecasepartyrolecombobox.hxx"

#include "datacollector.hxx"

#include "crimecasepartyrolegateway.hxx"

#include <algorithm>

CrimeCasePartyRoleComboBox::CrimeCasePartyRoleComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &CrimeCasePartyRoleComboBox::onCurrentDatasetChanged);
    reload();
}

void CrimeCasePartyRoleComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentCrimeCasePartyRoleChanged(std::dynamic_pointer_cast<CrimeCasePartyRole>(s));
}

StorableSPtr CrimeCasePartyRoleComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_roles.begin(), m_roles.end(), [=](CrimeCasePartyRoleSPtr cand) { return (cand->name() == txt); });

    if (m_roles.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void CrimeCasePartyRoleComboBox::implReload()
{
    try {
        clear();
        m_roles = CrimeCasePartyRoleGateway().loadAll();

        for (auto p : m_roles) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Crime Case Party Role list"), this);
    }
}

