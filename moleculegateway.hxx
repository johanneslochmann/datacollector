#pragma once

#include <QString>

class MoleculeGateway
{
public:
    MoleculeGateway();

    int loadIdFromName(const QString& name);
};
