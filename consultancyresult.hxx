#pragma once

#include "storable.hxx"

class ConsultancyResult;
using ConsultancyResultSPtr = std::shared_ptr<ConsultancyResult>;
using ConsultancyResultSPtrVector = std::vector<ConsultancyResultSPtr>;

class ConsultancyResult: public Storable {
public:
    ConsultancyResult();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};
