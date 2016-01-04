#include "informationsourceforcrimecasetablewidget.hxx"

#include <QStringList>
#include <QDebug>
#include <QMessageBox>
#include <QDebug>

#include "datacollector.hxx"

#include "informationsourceforcrimecasegateway.hxx"
#include "informationsourceforcrimecasedialog.hxx"
#include "crimecase.hxx"
#include "informationsourcetype.hxx"

InformationSourceForCrimeCaseTableWidget::InformationSourceForCrimeCaseTableWidget(QWidget *p)
    : DataTableWidget(p)
{
    m_headerLabels << tr("Source Type")
                   << tr("URL")
                   << tr("When Added")
                   << tr("Description")
                   << tr("ID");

    connect(this, &DataTableWidget::currentItemChanged, this, &InformationSourceForCrimeCaseTableWidget::onActivated);
}

void InformationSourceForCrimeCaseTableWidget::reload()
{
    clear();

    if (!m_crimeCase) {
        return;
    }

    try {
        InformationSourceForCrimeCaseGateway().loadAllInCrimeCase(m_crimeCase);
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load information sources for crime case."), this);
    }

    setRowCount(m_crimeCase->informationSources().size());
    setColumnCount(m_idCol + 1);

    setHorizontalHeaderLabels(m_headerLabels);;

    int r=0;

    for (auto i : m_crimeCase->informationSources()) {
        int m_sourceTypeNameCol { 0 };
        int m_urlCol { m_sourceTypeNameCol + 1 };
        int m_whenAddedCol { m_urlCol + 1 };
        int m_descriptionCol { m_whenAddedCol + 1 };
        int m_idCol { m_descriptionCol + 1 };

        setItem(r, m_sourceTypeNameCol, new QTableWidgetItem(format(i->informationSourceType())));
        setItem(r, m_urlCol, new QTableWidgetItem(i->url()));
        setItem(r, m_whenAddedCol, new QTableWidgetItem(i->whenAdded().toString()));
        setItem(r, m_descriptionCol, new QTableWidgetItem(i->description()));
        setItem(r, m_idCol, new QTableWidgetItem(QString("%1").arg(i->id())));

        r++;
    }
}

void InformationSourceForCrimeCaseTableWidget::editSelected()
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
        auto InformationSourceForCrimeCase = InformationSourceForCrimeCaseGateway().loadById(id);

        auto dlg = new InformationSourceForCrimeCaseDialog(this, InformationSourceForCrimeCase);

        dlg->exec();

        reload();
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, QObject::tr("Failed to delete information source record."));
    }
}

void InformationSourceForCrimeCaseTableWidget::deleteSelected()
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

    InformationSourceForCrimeCaseGateway().remove(idItm->data(Qt::DisplayRole).toInt());
    reload();
}

void InformationSourceForCrimeCaseTableWidget::onActivated(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    (void) previous;

    if (!currentItem()) {
        emit informationSourceForCrimeCaseActivated(0);
        return;
    }

    auto idItm = item(current->row(), m_idCol);

    if (!idItm) {
        emit informationSourceForCrimeCaseActivated(0);
        return;
    }

    emit informationSourceForCrimeCaseActivated(idItm->data(Qt::DisplayRole).toInt());
}

void InformationSourceForCrimeCaseTableWidget::setCrimeCase(CrimeCaseSPtr c)
{
    m_crimeCase = c;
    reload();
}

QString InformationSourceForCrimeCaseTableWidget::format(InformationSourceTypeSPtr t) const
{
    return t->name();
}
