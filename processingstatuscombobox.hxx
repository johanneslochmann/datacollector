#pragma once

#include "datacombobox.hxx"

#include "processingstatus.hxx"

class ProcessingStatusComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit ProcessingStatusComboBox(QWidget* p);

signals:
    void currentProcessingStatusChanged(ProcessingStatusSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    ProcessingStatusSPtrVector m_ProcessingStatuss;
};
