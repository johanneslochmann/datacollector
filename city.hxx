#pragma once

#include "storable.hxx"

class City;
using CitySPtr = std::shared_ptr<City>;
using CitySPtrVector = std::vector<CitySPtr>;

class City: public Storable {
public:
    City();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};
