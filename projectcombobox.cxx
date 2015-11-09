#include "projectcombobox.hxx"

#include "datacollector.hxx"
#include "projectdatagateway.hxx"

#include <algorithm>

ProjectComboBox::ProjectComboBox(QWidget* p)
    : DataComboBox(p)
{
    connect(this, &DataComboBox::datasetActivated, this, &ProjectComboBox::onCurrentDatasetChanged);
    reload();
}

void ProjectComboBox::onCurrentDatasetChanged(StorableSPtr s)
{
    emit currentProjectChanged(std::dynamic_pointer_cast<Project>(s));
}

StorableSPtr ProjectComboBox::storableForText(const QString &txt) const
{
    auto it = std::find_if(m_projects.begin(), m_projects.end(), [=](ProjectSPtr cand) { return (cand->name() == txt); });

    if (m_projects.end() != it) {
       return *it;
    }

    return std::make_shared<Storable>();
}

void ProjectComboBox::implReload()
{
    try {
        clear();
        m_projects = ProjectDataGateway().loadAll();

        for (auto p : m_projects) {
            addItem(p->name(), p->id());
        }

        addItem(QString(), 0);
        setCurrentText(QString());
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load project list"), this);
    }
}

