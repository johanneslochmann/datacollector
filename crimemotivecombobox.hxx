#pragma once

#include "datacombobox.hxx"

#include "crimemotive.hxx"

class CrimeMotiveComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit CrimeMotiveComboBox(QWidget* p);

signals:
    void currentCrimeMotiveChanged(CrimeMotiveSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    CrimeMotiveSPtrVector m_cities;
};
