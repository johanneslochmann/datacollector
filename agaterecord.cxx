#include "agaterecord.hxx"

AgateRecord::AgateRecord()
    : m_proband(std::make_shared<Proband>()),
      m_organization(std::make_shared<Organization>())
{
}

