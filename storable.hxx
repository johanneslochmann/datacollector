#pragma once

#include <QString>

#include <memory>
#include <vector>

class Storable;
using StorableSPtr = std::shared_ptr<Storable>;

class Storable
{
public:
    Storable();
    virtual ~Storable();

    int id() const;

    void setId(int id);

    bool hasId() const { return (id() > 0); }

protected:

private:
    int m_id { 0 };
};

