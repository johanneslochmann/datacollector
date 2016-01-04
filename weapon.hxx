#pragma once

#include "storable.hxx"

#include <QString>

class Weapon;
using WeaponSPtr = std::shared_ptr<Weapon>;
using WeaponSPtrVector = std::vector<WeaponSPtr>;

class Weapon : public Storable
{
public:
    Weapon();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};
