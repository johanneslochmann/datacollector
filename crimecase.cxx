#include "crimecase.hxx"

CrimeCase::CrimeCase()
{

}

QString CrimeCase::name() const
{
    return m_name;
}

QString CrimeCase::description() const
{
    return m_description;
}

void CrimeCase::setDescription(const QString &description)
{
    m_description = description;
}

void CrimeCase::setHousingType(HousingTypeSPtr t)
{
    if (t) {
        m_housingType->setId(t->id());
        m_housingType->setName(t->name());
    } else {
        m_housingType->setId(0);
        m_housingType->setName(QString());
    }
}

void CrimeCase::setName(const QString &name)
{
    m_name = name;
}

void CrimeCase::setCrimeYear(int y)
{
    (y > 0) ? m_crimeYear.setValue(y) : m_crimeYear.setValue(QVariant(QVariant::Int));
}

void CrimeCase::setCrimeDate(const QDate &d) {
    d.isValid() ? m_crimeDate.setValue(d) : m_crimeDate.setValue(QVariant(QVariant::Date));

    if (d.isValid()) {
        setCrimeYear(d.year());
    }
}

void CrimeCase::setCrimeTime(const QTime &t)
{
    t.isValid() ? m_crimeTime.setValue(t) : m_crimeTime.setValue(QVariant(QVariant::Time));
}
