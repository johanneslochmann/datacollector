#pragma once

#include "storable.hxx"

class HousingType;
using HousingTypeSPtr = std::shared_ptr<HousingType>;
using HousingTypeSPtrVector = std::vector<HousingTypeSPtr>;

class HousingType: public Storable {
public:
    HousingType();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};
