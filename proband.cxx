#include "proband.hxx"

Proband::Proband()
{
}

QString Proband::label() const
{
    QStringList buf;

    if (!surname().isEmpty()) {
        buf.append(surname());
    }

    if (!firstName().isEmpty()) {
        buf.append(firstName());
    }

    if (!externalId().isEmpty()) {
        buf.append(externalId());
    }

    if (birthday().isValid()) {
        buf.append(birthday().toString(Qt::ISODate));
    }

    return buf.join(", ");
}

QString Proband::externalId() const
{
    return m_externalId;
}

void Proband::setExternalId(const QString &externalId)
{
    m_externalId = externalId;
}

QDate Proband::birthday() const
{
    return m_birthday;
}

void Proband::setBirthday(const QDate &birthday)
{
    m_birthday = birthday;
}

int Proband::heightInCm() const
{
    return m_heightInCm;
}

void Proband::setHeightInCm(int heightInCm)
{
    m_heightInCm = heightInCm;
}

QString Proband::sex() const
{
    return m_sex;
}

void Proband::setSex(const QString &sex)
{
    m_sex = sex;
}

int Proband::sexId() const
{
    return m_sexId;
}

void Proband::setSexId(int sexId)
{
    m_sexId = sexId;
}

QString Proband::description() const
{
    return m_description;
}

void Proband::setDescription(const QString &description)
{
    m_description = description;
}

QString Proband::firstName() const
{
    return m_firstName;
}

void Proband::setFirstName(const QString &firstName)
{
    m_firstName = firstName;
}

QString Proband::surname() const
{
    return m_surname;
}

void Proband::setSurname(const QString &surname)
{
    m_surname = surname;
}

int Proband::yearOfBirth() const
{
    return m_yearOfBirth;
}

void Proband::setYearOfBirth(int yearOfBirth)
{
    m_yearOfBirth = yearOfBirth;
}

