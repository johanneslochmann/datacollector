#include "agaterecord.hxx"

AgateRecord::AgateRecord()
    : m_project(std::make_shared<Project>()),
      m_campaign(std::make_shared<Campaign>()),
      m_proband(std::make_shared<Proband>()),
      m_organization(std::make_shared<Organization>()),
      m_survey(std::make_shared<Survey>()),
      m_sex(std::make_shared<Sex>())
{
}

void AgateRecord::removeDepot(int idx)
{
    m_depots.erase(m_depots.begin() + idx);
}

void AgateRecord::removeMedication(int idx)
{
    m_medication.erase(m_medication.begin() + idx);
}

void AgateRecord::removeDiagnosis(int idx)
{
    m_diagnosis.erase(m_diagnosis.begin() + idx);
}

