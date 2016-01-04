#pragma once

#include "datagateway.h"

#include "weapon.hxx"

class WeaponGateway : public DataGateway<Weapon>
{
public:
    WeaponGateway() : DataGateway<Weapon>() {}

protected:
    QString loadAllQueryText() const override;
    QString loadByIdQueryText() const override;
    void parse(std::shared_ptr<DataType> t, const QSqlRecord &rec) override;
};
