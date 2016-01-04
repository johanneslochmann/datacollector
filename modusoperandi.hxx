#pragma once

#include "storable.hxx"

class ModusOperandi;
using ModusOperandiSPtr = std::shared_ptr<ModusOperandi>;
using ModusOperandiSPtrVector = std::vector<ModusOperandiSPtr>;

class ModusOperandi: public Storable {
public:
    ModusOperandi();

    QString name() const;
    QString description() const;

    void setName(const QString &name);
    void setDescription(const QString &description);

private:
    QString m_name;
    QString m_description;
};
