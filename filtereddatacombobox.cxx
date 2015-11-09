#include "filtereddatacombobox.hxx"

FilteredDataComboBox::FilteredDataComboBox(QWidget* p)
    : DataComboBox(p)
{
}

void FilteredDataComboBox::onFilterChanged(StorableSPtr s)
{
    clear();

    m_currentFilter = s;

    if (hasFilter()) {
        implReload();
    }
}

