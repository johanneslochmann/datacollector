#pragma once

#include "crimecase.hxx"

#include <QSqlRecord>

class CrimeCaseGateway
{
public:
    CrimeCaseGateway();

    bool save(CrimeCaseSPtr c);
    void remove(int id);

    CrimeCaseSPtrVector loadAll();
    CrimeCaseSPtr loadById(int id);

protected:
    void insert(CrimeCaseSPtr c);
    void update(CrimeCaseSPtr c);
    void implDelete(int id);

private:
    void parse(CrimeCaseSPtr c, const QSqlRecord& rec);
};
