#pragma once

#include "storable.hxx"

#include <QString>

class ProcessingStatus;
using ProcessingStatusSPtr = std::shared_ptr<ProcessingStatus>;
using ProcessingStatusSPtrVector = std::vector<ProcessingStatusSPtr>;

class ProcessingStatus : public Storable
{
public:
    explicit ProcessingStatus();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

    bool hasName() const { return (!name().isEmpty()); }

private:
    QString m_name;
    QString m_description;
};

