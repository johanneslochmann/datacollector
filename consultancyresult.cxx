#include "consultancyresult.hxx"


ConsultancyResult::ConsultancyResult()
    : Storable() {
}

QString ConsultancyResult::name() const
{
    return m_name;
}

void ConsultancyResult::setName(const QString &name)
{
    m_name = name;
}

QString ConsultancyResult::description() const
{
    return m_description;
}

void ConsultancyResult::setDescription(const QString &description)
{
    m_description = description;
}
