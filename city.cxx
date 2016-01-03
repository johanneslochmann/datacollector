#include "city.hxx"


City::City()
    : Storable() {
}

QString City::name() const
{
    return m_name;
}

void City::setName(const QString &name)
{
    m_name = name;
}

QString City::description() const
{
    return m_description;
}

void City::setDescription(const QString &description)
{
    m_description = description;
}
