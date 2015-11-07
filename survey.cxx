#include "survey.hxx"

Survey::Survey()
    : Storable()
{
}

QString Survey::probandLabel() const
{
    return m_probandLabel;
}

void Survey::setProbandLabel(const QString &probandLabel)
{
    m_probandLabel = probandLabel;
}

QString Survey::campaignLabel() const
{
    return m_campaignLabel;
}

void Survey::setCampaignLabel(const QString &campaignLabel)
{
    m_campaignLabel = campaignLabel;
}

QDate Survey::date() const
{
    return m_date;
}

void Survey::setDate(const QDate &date)
{
    m_date = date;
}

int Survey::probandId() const
{
    return m_probandId;
}

void Survey::setProbandId(int probandId)
{
    m_probandId = probandId;
}

int Survey::campaignId() const
{
    return m_campaignId;
}

void Survey::setCampaignId(int campaignId)
{
    m_campaignId = campaignId;
}

int Survey::organizationUnitId() const
{
    return m_organizationUnitId;
}

void Survey::setOrganizationUnitId(int organizationUnitId)
{
    m_organizationUnitId = organizationUnitId;
}

QString Survey::organizationUnit() const
{
    return m_organizationUnit;
}

void Survey::setOrganizationUnit(const QString &organizationUnit)
{
    m_organizationUnit = organizationUnit;
}

QString Survey::description() const
{
    return m_description;
}

void Survey::setDescription(const QString &description)
{
    m_description = description;
}

int Survey::smokingHabitId() const
{
    return m_smokingHabitId;
}

void Survey::setSmokingHabitId(int smokingHabitId)
{
    m_smokingHabitId = smokingHabitId;
}

double Survey::bmi() const
{
    return m_bmi;
}

void Survey::setBmi(double bmi)
{
    m_bmi = bmi;
}

