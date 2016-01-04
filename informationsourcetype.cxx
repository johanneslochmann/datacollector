#include "informationsourcetype.hxx"

InformationSourceType::InformationSourceType()
    : Storable() {
}

QString InformationSourceType::name() const
{
    return m_name;
}

void InformationSourceType::setName(const QString &name)
{
    m_name = name;
}

QString InformationSourceType::description() const
{
    return m_description;
}

void InformationSourceType::setDescription(const QString &description)
{
    m_description = description;
}
