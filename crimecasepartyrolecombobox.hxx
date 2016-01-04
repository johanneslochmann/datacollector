#pragma once

#include "datacombobox.hxx"

#include "crimecasepartyrole.hxx"

class CrimeCasePartyRoleComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit CrimeCasePartyRoleComboBox(QWidget* p);

signals:
    void currentCrimeCasePartyRoleChanged(CrimeCasePartyRoleSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    CrimeCasePartyRoleSPtrVector m_roles;
};
