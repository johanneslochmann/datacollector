#include "storable.hxx"

Storable::~Storable()
{
}

Storable::Storable()
{

}

int Storable::id() const
{
    return m_id;
}

void Storable::setId(int id)
{
    m_id = id;
}

