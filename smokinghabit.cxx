#include "smokinghabit.hxx"

SmokingHabit::SmokingHabit()
{
}

QString SmokingHabit::name() const
{
    return m_name;
}

void SmokingHabit::setName(const QString &name)
{
    m_name = name;
}

QString SmokingHabit::description() const
{
    return m_description;
}

int SmokingHabit::maxCigarettes() const
{
    return m_maxCigarettes;
}

void SmokingHabit::setDescription(const QString &description)
{
    m_description = description;
}

void SmokingHabit::setMaxCigarettes(int i)
{
    m_maxCigarettes = i;
}

