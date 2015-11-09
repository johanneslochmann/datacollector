#include "agatedepottablewidget.hxx"

#include "agatedepotdialog.hxx"

AgateDepotTableWidget::AgateDepotTableWidget(QWidget *p, AgateRecordSPtr r)
    : QTableWidget(p), m_r(r)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    reload();
}

void AgateDepotTableWidget::create()
{
    auto dlg = new AgateDepotDialog(this);

    if (QDialog::Accepted == dlg->exec()) {
        m_r->addDepot(dlg->depot());
        reload();
    }
}

void AgateDepotTableWidget::remove()
{
    auto selIdx = selectedIndexes();

    if (selIdx.isEmpty()) {
        return;
    }

    m_r->removeDepot(selIdx.first().row());

    reload();
}

void AgateDepotTableWidget::reload()
{
    clear();

    auto depots = m_r->depots();

    QStringList h;
    h << tr("Prescribeable Drug") << tr("Last Injection") << tr("Dosage in mg") << tr("Interval in days");

    setRowCount(depots.size());
    setColumnCount(4);
    setHorizontalHeaderLabels(h);

    int r = 0;
    for (auto i : depots) {
        setItem(r, 0, new QTableWidgetItem(i->prescribeableDrugName));
        setItem(r, 1, new QTableWidgetItem(i->lastInjectionDate.toString("dd.MM.yyyy")));
        setItem(r, 2, new QTableWidgetItem(QString("%1").arg(i->dosageInMg)));
        setItem(r, 3, new QTableWidgetItem(QString("%1").arg(i->injectionIntervalInDays)));

        r++;
    }
}

