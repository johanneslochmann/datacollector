#pragma once

#include "storable.hxx"

class CrimeMotive;
using CrimeMotiveSPtr = std::shared_ptr<CrimeMotive>;
using CrimeMotiveSPtrVector = std::vector<CrimeMotiveSPtr>;

class CrimeMotive: public Storable {
public:
    CrimeMotive();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};
