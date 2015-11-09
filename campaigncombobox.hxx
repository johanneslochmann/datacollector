#pragma once

#include "filtereddatacombobox.hxx"

#include "campaign.hxx"

class CampaignComboBox : public FilteredDataComboBox
{
    Q_OBJECT
public:
    explicit CampaignComboBox(QWidget* p);

signals:
    void currentCampaignChanged(CampaignSPtr c);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    CampaignSPtrVector m_campaigns;
};
