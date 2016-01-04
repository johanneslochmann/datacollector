#include "processingstatus.hxx"

ProcessingStatus::ProcessingStatus()
    : Storable()
{
}

QString ProcessingStatus::name() const
{
    return m_name;
}

QString ProcessingStatus::description() const
{
    return m_description;
}

void ProcessingStatus::setName(const QString &name)
{
    m_name = name;
}

void ProcessingStatus::setDescription(const QString &description)
{
    m_description = description;
}

