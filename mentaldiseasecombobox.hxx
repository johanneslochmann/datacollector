#pragma once

#include "datacombobox.hxx"

#include "mentaldisease.hxx"

class MentalDiseaseComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit MentalDiseaseComboBox(QWidget* p);

signals:
    void currentMentalDiseaseChanged(MentalDiseaseSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    MentalDiseaseSPtrVector m_MentalDiseases;
};
