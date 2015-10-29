#pragma once

#include <memory>
#include <vector>

class Storable
{
public:
    virtual ~Storable();

    int id() const;

    void setId(int id);

    bool hasId() const { return (id() > 0); }

protected:
    Storable();

private:
    int m_id { 0 };
};

