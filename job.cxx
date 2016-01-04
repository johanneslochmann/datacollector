#include "job.hxx"


Job::Job()
    : Storable() {
}

QString Job::name() const
{
    return m_name;
}

void Job::setName(const QString &name)
{
    m_name = name;
}

QString Job::description() const
{
    return m_description;
}

void Job::setDescription(const QString &description)
{
    m_description = description;
}
