#pragma once

#include <QString>

class PrescribeableDrugGateway
{
public:
    PrescribeableDrugGateway();

    int loadIdFromName(const QString& name);
};
