#include "prescribeabledrugselectiondialog.hxx"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QDoubleValidator>

#include "ui_prescribeabledrugselectiondialog.h"

#include "datacollector.hxx"

PrescribeableDrugSelectionDialog::PrescribeableDrugSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::unique_ptr<Ui::PrescribeableDrugSelectionDialog>(new Ui::PrescribeableDrugSelectionDialog))
{
    ui->setupUi(this);

    ui->m_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_data->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->morningW->setValidator(new QDoubleValidator(this));
    ui->lunchW->setValidator(new QDoubleValidator(this));
    ui->noonW->setValidator(new QDoubleValidator(this));
    ui->nightW->setValidator(new QDoubleValidator(this));

    connect(ui->morningW, &QLineEdit::textChanged, this, &PrescribeableDrugSelectionDialog::onMorningDosageChanged);
    connect(ui->lunchW, &QLineEdit::textChanged, this, &PrescribeableDrugSelectionDialog::onLunchDosageChanged);
    connect(ui->noonW, &QLineEdit::textChanged, this, &PrescribeableDrugSelectionDialog::onNoonDosageChanged);
    connect(ui->nightW, &QLineEdit::textChanged, this, &PrescribeableDrugSelectionDialog::onNightDosageChanged);

    m_m = new QSqlQueryModel(this);

    try {
        m_q = DataCollector::get()->prepareAndPerformQuery("select "
                                                           "pd.name as name, pd.dosage as dosage, u.name as dosage_unit, pd.id as id "
                                                           "from core.prescribeable_drug pd "
                                                           "join core.unit u on pd.dosage_unit_id = u.id "
                                                           "order by pd.name asc, pd.dosage asc;", false);
        m_m->setQuery(m_q);

        ui->m_data->setModel(m_m);
        ui->m_data->hideColumn(3);
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Prescribeable Drug list."), this);
    }

    connect(ui->m_data, &QTableView::activated, this, &PrescribeableDrugSelectionDialog::onIndexActivated);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

PrescribeableDrugSelectionDialog::~PrescribeableDrugSelectionDialog()
{

}

void PrescribeableDrugSelectionDialog::onIndexActivated(const QModelIndex &idx)
{
    auto idIdx = ui->m_data->model()->index(idx.row(), 3);

    m_selectedId = ui->m_data->model()->data(idIdx).toInt();

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_selectedId > 0);
}

void PrescribeableDrugSelectionDialog::onMorningDosageChanged(const QString &s)
{
    m_morningDosage = s.toDouble();
}

void PrescribeableDrugSelectionDialog::onLunchDosageChanged(const QString &s)
{
    m_lunchDosage = s.toDouble();
}

void PrescribeableDrugSelectionDialog::onNoonDosageChanged(const QString &s)
{
    m_noonDosage = s.toDouble();
}

void PrescribeableDrugSelectionDialog::onNightDosageChanged(const QString &s)
{
    m_nightDosage = s.toDouble();
}
