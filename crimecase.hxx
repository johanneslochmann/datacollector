#pragma once

#include <QString>
#include <QVariant>
#include <QDate>

#include <memory>
#include <vector>

#include "housingtype.hxx"

struct CityData {
    QString name;
    int id;
};

using CityDataSPtr = std::shared_ptr<CityData>;

class CrimeCase;
using CrimeCaseSPtr = std::shared_ptr<CrimeCase>;
using CrimeCaseSPtrVector = std::vector<CrimeCaseSPtr>;

class CrimeCase
{
public:
    CrimeCase();
    virtual ~CrimeCase() {}

    bool hasId() const { return (id() > 0); }
    bool hasName() const { return (!name().isEmpty()); }
    bool hasCrimeYear() const { return (!m_crimeYear.isNull()); }
    bool hasCrimeDate() const { return (!m_crimeDate.isNull()); }
    bool hasCrimeTime() const { return (!m_crimeTime.isNull()); }

    void setId(const int& id) { m_id = id; }
    void setName(const QString &name);
    void setCrimeYear(int y);
    void setCrimeDate(const QDate& d);
    void setCrimeTime(const QTime& t);
    void setDescription(const QString &description);

    void setHousingType(HousingTypeSPtr t);

    int id() const { return m_id; }
    QString name() const;
    CityDataSPtr city() const { return m_city; }
    HousingTypeSPtr housingType() const { return m_housingType; }
    QVariant crimeYear() const { return m_crimeYear; }
    QVariant crimeDate() const { return m_crimeDate; }
    QVariant crimeTime() const { return m_crimeTime; }
    QString description() const;

private:
    int m_id { 0 };
    QString m_name { "" };
    QVariant m_crimeYear { QVariant(QVariant::Int) };
    QVariant m_crimeDate { QVariant(QVariant::Date) };
    QVariant m_crimeTime { QVariant(QVariant::Time) };
    QString m_description { "" };

    CityDataSPtr m_city { std::make_shared<CityData>() };
    HousingTypeSPtr m_housingType { std::make_shared<HousingType>() };
};

