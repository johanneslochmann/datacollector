#include "housingtype.hxx"


HousingType::HousingType()
    : Storable() {
}

QString HousingType::name() const
{
    return m_name;
}

void HousingType::setName(const QString &name)
{
    m_name = name;
}

QString HousingType::description() const
{
    return m_description;
}

void HousingType::setDescription(const QString &description)
{
    m_description = description;
}
