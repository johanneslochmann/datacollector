#include "crimecaseparticipanttablewidget.hxx"

#include <QStringList>
#include <QMessageBox>

#include "datacollector.hxx"

#include "crimecasegateway.hxx"
#include "crimecaseparticipantgateway.hxx"
#include "crimecaseparticipant.hxx"
#include "crimecaseparticipantdialog.hxx"

CrimeCaseParticipantTableWidget::CrimeCaseParticipantTableWidget(QWidget *p)
    : DataTableWidget(p)
{
    m_headerLabels << tr("Role") << tr("Crime Type") << tr("Name") << tr("Sex") << tr("Age")
                   << tr("Job") << tr("ID");

    connect(this, &DataTableWidget::currentItemChanged, this, &CrimeCaseParticipantTableWidget::onActivated);
}

void CrimeCaseParticipantTableWidget::onCrimeCaseChanged(CrimeCaseSPtr c)
{
    m_crimeCase = c;
    reload();
}

void CrimeCaseParticipantTableWidget::reload()
{
    clear();

    if (m_crimeCase->id() < 1) {
        return;
    }

    try {
        CrimeCaseParticipantGateway().loadAllInCrimeCase(m_crimeCase);
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load crime case participants."), this);
    }

    setRowCount(m_crimeCase->participants().size());
    setColumnCount(m_idCol + 1);

    setHorizontalHeaderLabels(m_headerLabels);;

    int r=0;

    for (auto i : m_crimeCase->participants()) {
        setItem(r, m_participantRoleCol, new QTableWidgetItem(format(i->role())));
        setItem(r, m_nameCol, new QTableWidgetItem(i->name()));
        setItem(r, m_idCol, new QTableWidgetItem(QString("%1").arg(i->id())));
        setItem(r, m_ageCol, new QTableWidgetItem(QString("%1").arg(i->ageInYears())));
        setItem(r, m_sexCol, new QTableWidgetItem(format(i->sex())));
        setItem(r, m_crimeTypeCol, new QTableWidgetItem(format(i->crimeType())));
        setItem(r, m_jobCol, new QTableWidgetItem(format(i->job())));

        r++;
    }
}

void CrimeCaseParticipantTableWidget::editSelected()
{
    auto itm = currentItem();

    if (!itm) {
        return;
    }

    auto idItm = item(itm->row(), m_idCol);

    if (!idItm) {
        return;
    }

    auto id = idItm->data(Qt::DisplayRole).toInt();

    if (id < 1) {
        QMessageBox::information(this, tr("Hint"), tr("No Participant selected"));
        return;
    }

    try {
        auto b = CrimeCaseParticipantGateway().loadById(id);
        b->setCrimeCase(m_crimeCase);
        CrimeCaseParticipantGateway().loadSubRecords(b);

        auto dlg = new CrimeCaseParticipantDialog(this, b);

        dlg->show();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, QObject::tr("Failed to delete crime case participant record."));
    }
}

void CrimeCaseParticipantTableWidget::deleteSelected()
{
    auto itm = currentItem();

    if (!itm) {
        return;
    }

    auto idItm = item(itm->row(), m_idCol);

    if (!idItm) {
        return;
    }

    if (QMessageBox::Yes != QMessageBox::warning(this,
                                                 tr("Delete Participant?"),
                                                 tr("<p>Delete Participant %1?</p>")
                                                 .arg(idItm->data(Qt::DisplayRole).toInt()),
                                                 QMessageBox::Yes | QMessageBox::No)) {
        return;
    }

    CrimeCaseParticipantGateway().remove(idItm->data(Qt::DisplayRole).toInt());
    reload();
}

void CrimeCaseParticipantTableWidget::onActivated(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    (void) previous;

    if (!currentItem()) {
        emit crimeCaseParticipantActivated(0);
        return;
    }

    auto idItm = item(current->row(), m_idCol);

    if (!idItm) {
        emit crimeCaseParticipantActivated(0);
        return;
    }

    emit crimeCaseParticipantActivated(idItm->data(Qt::DisplayRole).toInt());
}

QString CrimeCaseParticipantTableWidget::format(CrimeCasePartyRoleSPtr r) const
{
    return r->name();
}

QString CrimeCaseParticipantTableWidget::format(SexSPtr s) const
{
    return s->name();
}

QString CrimeCaseParticipantTableWidget::format(CrimeTypeSPtr t) const
{
    return t->name();
}

QString CrimeCaseParticipantTableWidget::format(JobSPtr j) const
{
    return j->name();
}

QString CrimeCaseParticipantTableWidget::format(CrimeMotiveSPtr m) const
{
    return m->name();
}

