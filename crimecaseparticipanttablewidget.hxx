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
    QString format(CrimeCasePartyRoleSPtr r) const;
    QString format(SexSPtr s) const;

private:
    CrimeCaseSPtr m_crimeCase;

    QStringList m_headerLabels;
    int m_participantRoleCol { 0 };
    int m_crimeTypeCol { m_participantRoleCol + 1 };
    int m_modusOperandiCol { m_crimeTypeCol + 1 };
    int m_nameCol { m_modusOperandiCol + 1 };
    int m_sexCol { m_nameCol + 1 };
    int m_ageCol { m_sexCol + 1 };
    int m_professionCol { m_ageCol + 1 };
    int m_idCol { m_professionCol + 1 };

};

