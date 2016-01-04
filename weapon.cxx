#include "weapon.hxx"

Weapon::Weapon()
{
}

QString Weapon::name() const
{
    return m_name;
}

void Weapon::setName(const QString &name)
{
    m_name = name;
}

QString Weapon::description() const
{
    return m_description;
}

void Weapon::setDescription(const QString &description)
{
    m_description = description;
}

