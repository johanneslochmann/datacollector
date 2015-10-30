#include "organization.hxx"

Organization::Organization()
{
}

QString Organization::name() const
{
    return m_name;
}

void Organization::setName(const QString &name)
{
    m_name = name;
}

QString Organization::description() const
{
    return m_description;
}

void Organization::setDescription(const QString &description)
{
    m_description = description;
}

