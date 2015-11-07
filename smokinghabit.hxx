#pragma once

#include "storable.hxx"

#include <QString>

class SmokingHabit;
using SmokingHabitSPtr = std::shared_ptr<SmokingHabit>;
using SmokingHabitSPtrVector = std::vector<SmokingHabitSPtr>;

class SmokingHabit : public Storable
{
public:
    SmokingHabit();

    QString name() const;
    QString description() const;
    int maxCigarettes() const;

    void setName(const QString &name);
    void setDescription(const QString &description);
    void setMaxCigarettes(int i);

private:
    QString m_name;
    QString m_description;
    int m_maxCigarettes { 0 };
};
