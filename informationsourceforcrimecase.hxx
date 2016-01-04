#pragma once

#include "storable.hxx"

#include <QDateTime>

class InformationSourceType;
class InformationSourceForCrimeCase;
class CrimeCase;

using InformationSourceTypeSPtr = std::shared_ptr<InformationSourceType>;
using CrimeCaseSPtr = std::shared_ptr<CrimeCase>;
using InformationSourceForCrimeCaseSPtr = std::shared_ptr<InformationSourceForCrimeCase>;

using InformationSourceForCrimeCaseSPtrVector = std::vector<InformationSourceForCrimeCaseSPtr>;

class InformationSourceForCrimeCase: public Storable {
public:
    InformationSourceForCrimeCase();

    QString url() const;
    QString description() const;
    CrimeCaseSPtr crimeCase() const;
    InformationSourceTypeSPtr informationSourceType() const { return m_informationSourceType; }
    QDateTime whenAdded() const;

    void setUrl(const QString &url);
    void setDescription(const QString &description);
    void setCrimeCase(const CrimeCaseSPtr &crimeCase);
    void setWhenAdded(const QDateTime &whenAdded);
    void setInformationSourceType(InformationSourceTypeSPtr t) { m_informationSourceType = t; }

private:
    QString m_url;
    QString m_description { "" };
    QDateTime m_whenAdded { QDateTime::currentDateTime() };

    CrimeCaseSPtr m_crimeCase;
    InformationSourceTypeSPtr m_informationSourceType;
};
