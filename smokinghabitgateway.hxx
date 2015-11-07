#pragma once

#include "datagateway.h"

#include "smokinghabit.hxx"

class SmokingHabitGateway : public DataGateway<SmokingHabit>
{
public:
    SmokingHabitGateway() : DataGateway<SmokingHabit>() {}

protected:
    QString loadAllQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
