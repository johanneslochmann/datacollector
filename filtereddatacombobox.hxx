#pragma once

#include "datacombobox.hxx"

class FilteredDataComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit FilteredDataComboBox(QWidget* p);

    StorableSPtr currentFilter() const { return m_currentFilter; }
    bool hasFilter() const { return (StorableSPtr() != m_currentFilter); }

signals:
    void datasetActivated(const StorableSPtr s);

public slots:
    void onFilterChanged(StorableSPtr s);

private:
    StorableSPtr m_currentFilter;
};
