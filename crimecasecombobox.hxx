#pragma once

#include "datacombobox.hxx"

#include "crimecase.hxx"

class CrimeCaseComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit CrimeCaseComboBox(QWidget* p);

signals:
    void currentCrimeCaseChanged(CrimeCaseSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    CrimeCaseSPtrVector m_crimeCases;
};
