#include "mentaldisease.hxx"


MentalDisease::MentalDisease()
    : Storable() {
}

QString MentalDisease::name() const
{
    return m_name;
}

void MentalDisease::setName(const QString &name)
{
    m_name = name;
}

QString MentalDisease::description() const
{
    return m_description;
}

void MentalDisease::setDescription(const QString &description)
{
    m_description = description;
}
