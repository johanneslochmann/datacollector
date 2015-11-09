#pragma once

#include "datacombobox.hxx"

#include "project.hxx"

class ProjectComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit ProjectComboBox(QWidget* p);

signals:
    void currentProjectChanged(ProjectSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    ProjectSPtrVector m_projects;
};
