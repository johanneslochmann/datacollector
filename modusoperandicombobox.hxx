#pragma once

#include "datacombobox.hxx"

#include "modusoperandi.hxx"

class ModusOperandiComboBox : public DataComboBox
{
    Q_OBJECT
public:
    explicit ModusOperandiComboBox(QWidget* p);

signals:
    void currentModusOperandiChanged(ModusOperandiSPtr p);

public slots:
    void onCurrentDatasetChanged(StorableSPtr s);

protected:
    StorableSPtr storableForText(const QString &txt) const override;
    void implReload() override;

private:
    ModusOperandiSPtrVector m_ModusOperandis;
};
