#include "crimecasestablewidget.hxx"

#include <QStringList>
#include <QDebug>
#include <QMessageBox>
#include <QDebug>

#include "datacollector.hxx"
#include "crimecasegateway.hxx"
#include "crimecasedialog.hxx"

CrimeCasesTableWidget::CrimeCasesTableWidget(QWidget *p)
    : DataTableWidget(p)
{
    m_headerLabels << tr("Name")
                   << tr("City")
                   << tr("Housing Type")
                   << tr("Year")
                   << tr("Date")
                   << tr("Time")
                   << tr("ID");

    connect(this, &DataTableWidget::currentItemChanged, this, &CrimeCasesTableWidget::onActivated);
    connect(DataCollector::get(), &DataCollector::databaseAvailable, this, &CrimeCasesTableWidget::reload);
}

void CrimeCasesTableWidget::reload()
{
    clear();

    CrimeCaseSPtrVector buf;

    try {
        buf = CrimeCaseGateway().loadAll();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load crime cases."), this);
    }

    setRowCount(buf.size());
    setColumnCount(m_idCol + 1);

    setHorizontalHeaderLabels(m_headerLabels);;

    int r=0;

    for (auto i : buf) {
        setItem(r, m_nameCol, new QTableWidgetItem(i->name()));
        setItem(r, m_cityCol, new QTableWidgetItem(format(i->city())));
        setItem(r, m_housingTypeCol, new QTableWidgetItem(format(i->housingType())));
        setItem(r, m_crimeYearCol, new QTableWidgetItem(i->crimeYear().toString()));
        setItem(r, m_crimeDateCol, new QTableWidgetItem(i->crimeDate().toDate().toString("dd.MM.yyyy")));
        setItem(r, m_crimeTimeCol, new QTableWidgetItem(i->crimeTime().toTime().toString("HH:mm")));
        setItem(r, m_idCol, new QTableWidgetItem(QString("%1").arg(i->id())));

        r++;
    }
}

void CrimeCasesTableWidget::editSelected()
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
        QMessageBox::information(this, tr("Hint"), tr("No Crime Case selected"));
        return;
    }

    try {
        auto crimeCase = CrimeCaseGateway().loadById(id);

        qDebug() << "name: " << crimeCase->name();

        auto dlg = new CrimeCaseDialog(this, crimeCase);

        dlg->exec();

        reload();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, QObject::tr("Failed to delete Crime Case record."));
    }
}

void CrimeCasesTableWidget::deleteSelected()
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
                                                 tr("Delete Survey?"),
                                                 tr("<p>Delete Crime Case %1?</p>")
                                                 .arg(idItm->data(Qt::DisplayRole).toInt()),
                                                 QMessageBox::Yes | QMessageBox::No)) {
        return;
    }

    CrimeCaseGateway().remove(idItm->data(Qt::DisplayRole).toInt());
    reload();
}

void CrimeCasesTableWidget::onActivated(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    (void) previous;

    if (!currentItem()) {
        emit crimeCaseActivated(0);
        return;
    }

    auto idItm = item(current->row(), m_idCol);

    if (!idItm) {
        emit crimeCaseActivated(0);
        return;
    }

    emit crimeCaseActivated(idItm->data(Qt::DisplayRole).toInt());
}

QString CrimeCasesTableWidget::format(HousingTypeSPtr t) const
{
    return t->name();
}

QString CrimeCasesTableWidget::format(CitySPtr c) const
{
    return c->name();
}
