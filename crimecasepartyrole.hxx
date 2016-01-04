#pragma once

#include "storable.hxx"

class CrimeCasePartyRole;
using CrimeCasePartyRoleSPtr = std::shared_ptr<CrimeCasePartyRole>;
using CrimeCasePartyRoleSPtrVector = std::vector<CrimeCasePartyRoleSPtr>;

class CrimeCasePartyRole: public Storable {
public:
    CrimeCasePartyRole();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};
