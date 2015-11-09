#pragma once

#include "datacombobox.hxx"

#include "sex.hxx"

class SexComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit SexComboBox(QWidget* p);

signals:
    void currentSexChanged(SexSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    SexSPtrVector m_Sexs;
};
