#pragma once

#include "datacombobox.hxx"

#include "organization.hxx"

class OrganizationComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit OrganizationComboBox(QWidget* p);

signals:
    void currentOrganizationChanged(OrganizationSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    OrganizationSPtrVector m_organizations;
};
