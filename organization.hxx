#pragma once

#include "storable.hxx"

#include <QString>

class Organization;
using OrganizationSPtr = std::shared_ptr<Organization>;
using OrganizationSPtrVector = std::vector<OrganizationSPtr>;

class Organization : public Storable
{
public:
    Organization();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};
