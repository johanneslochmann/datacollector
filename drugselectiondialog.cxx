#include "drugselectiondialog.hxx"

#include <QPushButton>
#include <QDialogButtonBox>

#include "ui_drugselectiondialog.h"

#include "datacollector.hxx"

DrugSelectionDialog::DrugSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::unique_ptr<Ui::DrugSelectionDialog>(new Ui::DrugSelectionDialog))
{
    ui->setupUi(this);

    ui->m_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_data->setSelectionMode(QAbstractItemView::SingleSelection);

    m_m = new QSqlQueryModel(this);

    try {
        m_q = DataCollector::get()->prepareAndPerformQuery("select name, id from core.drug order by name asc;", false);
        m_m->setQuery(m_q);

        ui->m_data->setModel(m_m);
        ui->m_data->hideColumn(1);
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Drug list."), this);
    }

    connect(ui->m_data, &QTableView::activated, this, &DrugSelectionDialog::onIndexActivated);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

DrugSelectionDialog::~DrugSelectionDialog()
{
}

void DrugSelectionDialog::onIndexActivated(const QModelIndex &idx)
{
    auto idIdx = ui->m_data->model()->index(idx.row(), 1);

    m_selectedId = ui->m_data->model()->data(idIdx).toInt();

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_selectedId > 0);
}
