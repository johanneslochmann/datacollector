#pragma once

#include <QString>
#include <QVariant>
#include <QDate>

#include <memory>
#include <vector>

#include "storable.hxx"
#include "housingtype.hxx"
#include "city.hxx"
#include "informationsourceforcrimecase.hxx"

class CrimeCase;
using CrimeCaseSPtr = std::shared_ptr<CrimeCase>;
using CrimeCaseSPtrVector = std::vector<CrimeCaseSPtr>;

class CrimeCase: public Storable
{
public:
    CrimeCase();
    virtual ~CrimeCase() {}

    bool hasName() const { return (!name().isEmpty()); }
    bool hasCrimeYear() const { return (!m_crimeYear.isNull()); }
    bool hasCrimeDate() const { return (!m_crimeDate.isNull()); }
    bool hasCrimeTime() const { return (!m_crimeTime.isNull()); }

    void setName(const QString &name);
    void setCrimeYear(int y);
    void setCrimeDate(const QDate& d);
    void setCrimeTime(const QTime& t);
    void setDescription(const QString &description);

    void setHousingType(HousingTypeSPtr t);
    void setCity(CitySPtr c);

    QString name() const;
    CitySPtr city() const { return m_city; }
    HousingTypeSPtr housingType() const { return m_housingType; }
    QVariant crimeYear() const { return m_crimeYear; }
    QVariant crimeDate() const { return m_crimeDate; }
    QVariant crimeTime() const { return m_crimeTime; }
    QString description() const;

    void addInformationSource(InformationSourceForCrimeCaseSPtr i) { m_informationSources.push_back(i); }
    void removeInformationSource(InformationSourceForCrimeCaseSPtr i);
    const InformationSourceForCrimeCaseSPtrVector informationSources() const { return m_informationSources; }
    void setInformationSources(InformationSourceForCrimeCaseSPtrVector v) { m_informationSources = v; }

private:
    QString m_name { "" };
    QVariant m_crimeYear { QVariant(QVariant::Int) };
    QVariant m_crimeDate { QVariant(QVariant::Date) };
    QVariant m_crimeTime { QVariant(QVariant::Time) };
    QString m_description { "" };

    CitySPtr m_city { std::make_shared<City>() };
    HousingTypeSPtr m_housingType { std::make_shared<HousingType>() };
    InformationSourceForCrimeCaseSPtrVector m_informationSources;
};

