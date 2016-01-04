#pragma once

#include "storable.hxx"

class InformationSourceType;
using InformationSourceTypeSPtr = std::shared_ptr<InformationSourceType>;
using InformationSourceTypeSPtrVector = std::vector<InformationSourceTypeSPtr>;

class InformationSourceType: public Storable {
public:
    InformationSourceType();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};
