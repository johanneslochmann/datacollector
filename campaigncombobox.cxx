#include "campaigncombobox.hxx"

#include "campaigndatagateway.hxx"

CampaignComboBox::CampaignComboBox(QWidget* p)
    : FilteredDataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &CampaignComboBox::onCurrentDatasetChanged);
}

void CampaignComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentCampaignChanged(std::dynamic_pointer_cast<Campaign>(s));
}

StorableSPtr CampaignComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_campaigns.begin(), m_campaigns.end(), [=](CampaignSPtr c) { return (c->name() == txt); });

    if (m_campaigns.end() != it) {
        return *it;
    }

    return std::make_shared<Storable>();
}

void CampaignComboBox::implReload()
{
    clear();

    if (!hasFilter()) {
        return;
    }

    try {
        m_campaigns = CampaignDataGateway().campaignsInProject(currentFilter()->id());

        for (auto c : m_campaigns) {
            addItem(c->name(), c->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load campaigns in project"), this);
    }
}
