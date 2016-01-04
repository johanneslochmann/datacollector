#pragma once

#include "storable.hxx"

class CrimeType;
using CrimeTypeSPtr = std::shared_ptr<CrimeType>;
using CrimeTypeSPtrVector = std::vector<CrimeTypeSPtr>;

class CrimeType: public Storable {
public:
    CrimeType();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};
