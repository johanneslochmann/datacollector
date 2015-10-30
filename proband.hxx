#pragma once

#include "storable.hxx"

#include <QString>
#include <QDate>

class Proband;
using ProbandSPtr = std::shared_ptr<Proband>;
using ProbandSPtrVector = std::vector<ProbandSPtr>;

class Proband: public Storable
{
public:
    Proband();

    QString label() const;
    QString externalId() const;
    QDate birthday() const;
    int heightInCm() const;
    QString sex() const;
    int sexId() const;
    QString description() const;
    QString firstName() const;
    QString surname() const;

    void setExternalId(const QString &externalId);
    void setBirthday(const QDate &birthday);
    void setHeightInCm(int heightInCm);
    void setSex(const QString &sex);
    void setSexId(int sexId);
    void setDescription(const QString &description);
    void setFirstName(const QString &firstName);
    void setSurname(const QString &surname);

private:
    QString m_externalId;
    QDate m_birthday;
    int m_heightInCm;
    QString m_sex;
    int m_sexId { 0 };
    QString m_description;
    QString m_firstName;
    QString m_surname;
};
