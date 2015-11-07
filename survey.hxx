#pragma once

#include "storable.hxx"

#include <QString>
#include <QDate>

class Survey;
using SurveySPtr = std::shared_ptr<Survey>;
using SurveySPtrVector = std::vector<SurveySPtr>;

class Survey : public Storable
{
public:
    explicit Survey();

    QString probandLabel() const;
    QString campaignLabel() const;
    QString organizationUnit() const;
    QString description() const;
    QDate date() const;
    int probandId() const;
    int campaignId() const;
    int organizationUnitId() const;
    int smokingHabitId() const;

    void setProbandLabel(const QString &probandLabel);
    void setCampaignLabel(const QString &campaignLabel);
    void setDate(const QDate &date);
    void setProbandId(int probandId);
    void setCampaignId(int campaignId);
    void setOrganizationUnitId(int organizationUnitId);
    void setOrganizationUnit(const QString &organizationUnit);
    void setDescription(const QString &description);
    void setSmokingHabitId(int smokingHabitId);

private:
    QString m_probandLabel;
    QString m_campaignLabel;
    QString m_organizationUnit;
    QString m_description { "" };
    QDate m_date { QDate::currentDate() };

    int m_probandId { 0 };
    int m_campaignId { 0 };
    int m_organizationUnitId { 0 };
    int m_smokingHabitId { 1 };
};

