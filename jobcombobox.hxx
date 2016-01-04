#pragma once

#include "datacombobox.hxx"

#include "job.hxx"

class JobComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit JobComboBox(QWidget* p);

signals:
    void currentJobChanged(JobSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    JobSPtrVector m_jobs;
};
