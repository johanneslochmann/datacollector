#include "datacombobox.hxx"

#include "datacollector.hxx"

DataComboBox::DataComboBox(QWidget *p)
    : QComboBox(p)
{
    connect(this, &QComboBox::currentTextChanged, this, &DataComboBox::onItemActivated);

    connect(DataCollector::get(), &DataCollector::databaseAvailable, this, &DataComboBox::reload);
    connect(DataCollector::get(), &DataCollector::databaseAboutToClose, this, &DataComboBox::clear);
}

void DataComboBox::onItemActivated(const QString &txt)
{
    emit datasetActivated(storableForText(txt));
}

