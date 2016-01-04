#pragma once

#include "datacombobox.hxx"

#include "consultancyresult.hxx"

class ConsultancyResultComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit ConsultancyResultComboBox(QWidget* p);

signals:
    void currentConsultancyResultChanged(ConsultancyResultSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    ConsultancyResultSPtrVector m_cities;
};
