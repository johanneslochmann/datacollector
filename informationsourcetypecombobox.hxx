#pragma once

#include "datacombobox.hxx"

#include "informationsourcetype.hxx"

class InformationSourceTypeComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit InformationSourceTypeComboBox(QWidget* p);

signals:
    void currentInformationSourceTypeChanged(InformationSourceTypeSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    InformationSourceTypeSPtrVector m_informationSourceTypes;
};
