#include "agatemedicationtablewidget.hxx"

#include "agatemedicationdialog.hxx"

AgateMedicationTableWidget::AgateMedicationTableWidget(QWidget *p, AgateRecordSPtr r)
    : QTableWidget(p), m_r(r)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    reload();
}

void AgateMedicationTableWidget::create()
{
    auto dlg = new AgateMedicationDialog(this);

    if (QDialog::Accepted == dlg->exec()) {
        m_r->addMedication(dlg->Medication());
        reload();
    }
}

void AgateMedicationTableWidget::remove()
{
    auto selIdx = selectedIndexes();

    if (selIdx.isEmpty()) {
        return;
    }

    m_r->removeMedication(selIdx.first().row());

    reload();
}

void AgateMedicationTableWidget::reload()
{
    clear();

    auto medications = m_r->medication();

    QStringList h;
    h << tr("Molecule") << tr("Dosage in mg");

    setRowCount(medications.size());
    setColumnCount(2);
    setHorizontalHeaderLabels(h);

    int r = 0;
    for (auto i : medications) {
        setItem(r, 0, new QTableWidgetItem(i->moleculeName));
        setItem(r, 1, new QTableWidgetItem(QString("%1").arg(i->dosageInMg)));

        r++;
    }
}

