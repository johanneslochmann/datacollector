#include "agatediagnosistablewidget.hxx"

#include "agatediagnosisdialog.hxx"

AgateDiagnosisTableWidget::AgateDiagnosisTableWidget(QWidget *p, AgateRecordSPtr r)
    : QTableWidget(p), m_r(r)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    reload();
}

void AgateDiagnosisTableWidget::create()
{
    auto dlg = new AgateDiagnosisDialog(this);

    if (QDialog::Accepted == dlg->exec()) {
        m_r->addDiagnosis(dlg->Diagnosis());
        reload();
    }
}

void AgateDiagnosisTableWidget::remove()
{
    auto selIdx = selectedIndexes();

    if (selIdx.isEmpty()) {
        return;
    }

    m_r->removeDiagnosis(selIdx.first().row());

    reload();
}

void AgateDiagnosisTableWidget::reload()
{
    clear();

    auto buf = m_r->diagnosis();

    QStringList h;
    h << tr("Diagnosis");

    setRowCount(buf.size());
    setColumnCount(1);
    setHorizontalHeaderLabels(h);

    int r = 0;
    for (auto i : buf) {
        setItem(r, 0, new QTableWidgetItem(i->name));

        r++;
    }
}

