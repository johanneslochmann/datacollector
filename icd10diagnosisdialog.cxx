#include "icd10diagnosisdialog.hxx"

#include <QTableView>
#include <QDebug>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTextEdit>

#include "ui_icd10diagnosisdialog.h"

#include "datacollector.hxx"

Icd10DiagnosisDialog::Icd10DiagnosisDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::unique_ptr<Ui::Icd10DiagnosisDialog>(new Ui::Icd10DiagnosisDialog))
{
    ui->setupUi(this);

    ui->m_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_data->setSelectionMode(QAbstractItemView::SingleSelection);

    m_m = new QSqlQueryModel(this);

    try {
        m_q = DataCollector::get()->prepareAndPerformQuery(QStringLiteral("select name as \"%1\", id from core.icd10_diagnosis order by name asc;").arg(tr("Name")), false);
        m_m->setQuery(m_q);

        ui->m_data->setModel(m_m);
        ui->m_data->hideColumn(1);
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load ICD10 diagnosis list."), this);
    }

    connect(ui->m_data, &QTableView::activated, this, &Icd10DiagnosisDialog::onIndexActivated);
    connect(ui->m_comment, &QTextEdit::textChanged, this, &Icd10DiagnosisDialog::onCommentChanged);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

Icd10DiagnosisDialog::~Icd10DiagnosisDialog()
{
}

void Icd10DiagnosisDialog::onIndexActivated(const QModelIndex &idx)
{
    auto idIdx = ui->m_data->model()->index(idx.row(), 1);

    m_selectedId = ui->m_data->model()->data(idIdx).toInt();

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_selectedId > 0);
}

void Icd10DiagnosisDialog::onCommentChanged()
{
    m_comment = ui->m_comment->toPlainText();
}
