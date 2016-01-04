#pragma once

#include "storable.hxx"

class Job;
using JobSPtr = std::shared_ptr<Job>;
using JobSPtrVector = std::vector<JobSPtr>;

class Job: public Storable {
public:
    Job();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};
