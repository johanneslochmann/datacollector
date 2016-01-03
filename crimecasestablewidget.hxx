#pragma once

#include <datatablewidget.hxx>

#include "crimecase.hxx"

class CrimeCasesTableWidget : public DataTableWidget
{
    Q_OBJECT
public:
    explicit CrimeCasesTableWidget(QWidget* p);

    int idColumn() const { return m_idCol; }

signals:
    void crimeCaseActivated(int id);

public slots:
    void reload();
    void editSelected();
    void deleteSelected();
    void onActivated(QTableWidgetItem* current, QTableWidgetItem* previous);

protected:
    QString format(HousingTypeSPtr t) const;
    QString format(CityDataSPtr c) const;

private:
    QStringList m_headerLabels;
    int m_nameCol { 0 };
    int m_cityCol { m_nameCol + 1 };
    int m_housingTypeCol { m_cityCol + 1 };
    int m_crimeYearCol { m_housingTypeCol + 1 };
    int m_crimeDateCol { m_crimeYearCol + 1 };
    int m_crimeTimeCol { m_crimeDateCol + 1 };
    int m_idCol { m_crimeTimeCol + 1 };
};

