#pragma once

#include <QString>

class DiagnosisGateway
{
public:
    DiagnosisGateway();

    int loadIdFromName(const QString& name);
};
