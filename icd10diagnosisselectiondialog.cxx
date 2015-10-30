#include "icd10diagnosisselectiondialog.hxx"

#include <QTableView>
#include <QDebug>
#include <QDialogButtonBox>
#include <QPushButton>

#include "ui_icd10diagnosisselectiondialog.h"

#include "datacollector.hxx"

Icd10DiagnosisSelectionDialog::Icd10DiagnosisSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::unique_ptr<Ui::Icd10DiagnosisSelectionDialog>(new Ui::Icd10DiagnosisSelectionDialog))
{
    ui->setupUi(this);

    ui->m_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_data->setSelectionMode(QAbstractItemView::SingleSelection);

    m_m = new QSqlQueryModel(this);

    try {
        m_q = DataCollector::get()->prepareAndPerformQuery("select name, id from core.icd10_diagnosis order by name asc;", false);
        m_m->setQuery(m_q);

        ui->m_data->setModel(m_m);
        ui->m_data->hideColumn(1);
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load ICD10 diagnosis list."), this);
    }

    connect(ui->m_data, &QTableView::activated, this, &Icd10DiagnosisSelectionDialog::onIndexActivated);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

Icd10DiagnosisSelectionDialog::~Icd10DiagnosisSelectionDialog()
{
}

void Icd10DiagnosisSelectionDialog::onIndexActivated(const QModelIndex &idx)
{
    auto idIdx = ui->m_data->model()->index(idx.row(), 1);

    m_selectedId = ui->m_data->model()->data(idIdx).toInt();

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_selectedId > 0);
}
