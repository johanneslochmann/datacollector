#include "project.hxx"

Project::Project()
    : Storable()
{
}

QString Project::name() const
{
    return m_name;
}

void Project::setName(const QString &name)
{
    m_name = name;
}

QString Project::description() const
{
    return m_description;
}

void Project::setDescription(const QString &description)
{
    m_description = description;
}

