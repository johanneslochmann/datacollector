#pragma once

#include "storable.hxx"

class MentalDisease;
using MentalDiseaseSPtr = std::shared_ptr<MentalDisease>;
using MentalDiseaseSPtrVector = std::vector<MentalDiseaseSPtr>;

class MentalDisease: public Storable {
public:
    MentalDisease();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};
