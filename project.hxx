#pragma once

#include "storable.hxx"

#include <QString>

class Project;
using ProjectSPtr = std::shared_ptr<Project>;
using ProjectSPtrVector = std::vector<ProjectSPtr>;

class Project : public Storable
{
public:
    explicit Project();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

    bool hasName() const { return (!name().isEmpty()); }

private:
    QString m_name { "" };
    QString m_description { "" };
};

