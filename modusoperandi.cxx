#include "modusoperandi.hxx"


ModusOperandi::ModusOperandi()
    : Storable() {
}

QString ModusOperandi::name() const
{
    return m_name;
}

void ModusOperandi::setName(const QString &name)
{
    m_name = name;
}

QString ModusOperandi::description() const
{
    return m_description;
}

void ModusOperandi::setDescription(const QString &description)
{
    m_description = description;
}
