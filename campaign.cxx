#include "campaign.hxx"

Campaign::Campaign()
{
}

QString Campaign::name() const
{
    return m_name;
}

void Campaign::setName(const QString &name)
{
    m_name = name;
}

QDate Campaign::begin() const
{
    return m_begin;
}

void Campaign::setBegin(const QDate &begin)
{
    m_begin = begin;
}

QDate Campaign::end() const
{
    return m_end;
}

void Campaign::setEnd(const QDate &end)
{
    m_end = end;
}

QString Campaign::description() const
{
    return m_description;
}

void Campaign::setDescription(const QString &description)
{
    m_description = description;
}

QString Campaign::projectName() const
{
    return m_projectName;
}

void Campaign::setProjectName(const QString &projectName)
{
    m_projectName = projectName;
}

int Campaign::projectId() const
{
    return m_projectId;
}

void Campaign::setProjectId(int projectId)
{
    m_projectId = projectId;
}

