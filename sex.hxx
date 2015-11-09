#pragma once

#include "storable.hxx"

#include <QString>

class Sex;
using SexSPtr = std::shared_ptr<Sex>;
using SexSPtrVector = std::vector<SexSPtr>;

class Sex : public Storable
{
public:
    explicit Sex();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

    bool hasName() const { return (!name().isEmpty()); }

private:
    QString m_name;
    QString m_description;
};

