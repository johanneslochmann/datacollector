#include "informationsourceforcrimecase.hxx"

#include "informationsourcetype.hxx"

InformationSourceForCrimeCase::InformationSourceForCrimeCase()
    : Storable(), m_informationSourceType(std::make_shared<InformationSourceType>()) {
}

QString InformationSourceForCrimeCase::url() const
{
    return m_url;
}

void InformationSourceForCrimeCase::setUrl(const QString &name)
{
    m_url = name;
}

QString InformationSourceForCrimeCase::description() const
{
    return m_description;
}

void InformationSourceForCrimeCase::setDescription(const QString &description)
{
    m_description = description;
}

CrimeCaseSPtr InformationSourceForCrimeCase::crimeCase() const
{
    return m_crimeCase;
}

void InformationSourceForCrimeCase::setCrimeCase(const CrimeCaseSPtr &crimeCase)
{
    m_crimeCase = crimeCase;
}

QDateTime InformationSourceForCrimeCase::whenAdded() const
{
    return m_whenAdded;
}

void InformationSourceForCrimeCase::setWhenAdded(const QDateTime &whenAdded)
{
    m_whenAdded = whenAdded;
}
