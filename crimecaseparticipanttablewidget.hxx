#pragma once

#include <datatablewidget.hxx>

#include "crimecase.hxx"

class CrimeCaseParticipantTableWidget : public DataTableWidget
{
    Q_OBJECT
public:
    explicit CrimeCaseParticipantTableWidget(QWidget* p);

    int idColumn() const { return m_idCol; }

signals:
    void crimeCaseParticipantActivated(int id);

public slots:
    void onCrimeCaseChanged(CrimeCaseSPtr c);
    void reload();
    void editSelected();
    void deleteSelected();
    void onActivated(QTableWidgetItem* current, QTableWidgetItem* previous);

protected:

private:
    CrimeCaseSPtr m_crimeCase;

    QStringList m_headerLabels;
    int m_campaignCol { 0 };
    int m_probandCol { m_campaignCol + 1 };
    int m_surveyDateCol { m_probandCol + 1 };
    int m_organizationCol { m_surveyDateCol + 1 };
    int m_idCol { m_organizationCol + 1 };

};

