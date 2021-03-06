#pragma once

#include <QTableWidget>

#include "agaterecord.hxx"

class AgateMedicationTableWidget: public QTableWidget
{
    Q_OBJECT
public:
    explicit AgateMedicationTableWidget(QWidget* p, AgateRecordSPtr r);

signals:

public slots:
    void create();
    void remove();

    void reload();

private:
    AgateRecordSPtr m_r;
};
