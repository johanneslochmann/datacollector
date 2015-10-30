#include "depotdrugdialog.hxx"

#include <QLineEdit>
#include <QDateEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QPushButton>
#include <QDialogButtonBox>

#include "ui_depotdrugdialog.h"

#include "datacollector.hxx"

DepotDrugDialog::DepotDrugDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::unique_ptr<Ui::DepotDrugDialog>(new Ui::DepotDrugDialog))
{
    ui->setupUi(this);

    ui->m_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_data->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->dosage->setValidator(new QDoubleValidator(this));
    ui->interval->setValidator(new QIntValidator(this));
    ui->lastInjection->setDisplayFormat("dd.MM.yyyy");
    ui->lastInjection->setDate(QDate::currentDate());
    ui->lastInjection->setCalendarPopup(true);

    connect(ui->dosage, &QLineEdit::textChanged, this, &DepotDrugDialog::onDosageChanged);
    connect(ui->lastInjection, &QDateEdit::dateChanged, this, &DepotDrugDialog::onLastInjectionDateChanged);
    connect(ui->interval, &QLineEdit::textChanged, this, &DepotDrugDialog::onInjectionIntervalChanged);

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

    connect(ui->m_data, &QTableView::activated, this, &DepotDrugDialog::onIndexActivated);
}

DepotDrugDialog::~DepotDrugDialog()
{
}

void DepotDrugDialog::onIndexActivated(const QModelIndex &idx)
{
    auto idIdx = ui->m_data->model()->index(idx.row(), 3);

    m_selectedId = ui->m_data->model()->data(idIdx).toInt();

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_selectedId > 0);
}

void DepotDrugDialog::onLastInjectionDateChanged(const QDate &d)
{
    m_lastInjectionDate = d;
}

void DepotDrugDialog::onDosageChanged(const QString &s)
{
    m_dosage = s.toDouble();
}

void DepotDrugDialog::onInjectionIntervalChanged(const QString &s)
{
    m_injectionInterval = s.toInt();
}
