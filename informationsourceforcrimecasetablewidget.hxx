#pragma once

#include <datatablewidget.hxx>

#include "informationsourceforcrimecase.hxx"

class InformationSourceForCrimeCaseTableWidget : public DataTableWidget
{
    Q_OBJECT
public:
    explicit InformationSourceForCrimeCaseTableWidget(QWidget* p);

    int idColumn() const { return m_idCol; }

signals:
    void informationSourceForCrimeCaseActivated(int id);

public slots:
    void reload();
    void editSelected();
    void deleteSelected();
    void onActivated(QTableWidgetItem* current, QTableWidgetItem* previous);
    void setCrimeCase(CrimeCaseSPtr c);

protected:
    QString format(InformationSourceTypeSPtr t) const;

private:
    CrimeCaseSPtr m_crimeCase;

    QStringList m_headerLabels;
    int m_sourceTypeNameCol { 0 };
    int m_urlCol { m_sourceTypeNameCol + 1 };
    int m_whenAddedCol { m_urlCol + 1 };
    int m_descriptionCol { m_whenAddedCol + 1 };
    int m_idCol { m_descriptionCol + 1 };
};

