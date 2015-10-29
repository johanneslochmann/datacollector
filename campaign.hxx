#pragma once

#include "storable.hxx"

#include <QString>
#include <QDate>

class Campaign;
using CampaignSPtr = std::shared_ptr<Campaign>;
using CampaignSPtrVector = std::vector<CampaignSPtr>;

class Campaign : public Storable
{
public:
    Campaign();

    QString name() const;
    QDate begin() const;
    QDate end() const;
    QString description() const;
    QString projectName() const;
    void setProjectId(int projectId);

    void setName(const QString &name);
    void setBegin(const QDate &begin);
    void setEnd(const QDate &end);
    void setDescription(const QString &description);
    void setProjectName(const QString &projectName);
    int projectId() const;

private:
    QString m_name;
    QDate m_begin;
    QDate m_end;
    QString m_description;
    QString m_projectName;
    int m_projectId { 0 };
};
