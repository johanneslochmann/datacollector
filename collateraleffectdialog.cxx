#include "collateraleffectdialog.hxx"

#include <QPushButton>
#include <QTableView>
#include <QTextEdit>

#include "ui_collateraleffectdialog.h"

#include "datacollector.hxx"

CollateralEffectDialog::CollateralEffectDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::unique_ptr<Ui::CollateralEffectDialog>(new Ui::CollateralEffectDialog))
{
    ui->setupUi(this);

    ui->m_d->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_d->setSelectionMode(QAbstractItemView::SingleSelection);

    m_m = new QSqlQueryModel(this);

    try {
        m_q = DataCollector::get()->prepareAndPerformQuery(QStringLiteral("select name as \"%1\", id from core.collateral_effect order by name asc;").arg(tr("Name")), false);
        m_m->setQuery(m_q);

        ui->m_d->setModel(m_m);
        ui->m_d->hideColumn(1);
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Collateral Effects list."), this);
    }

    connect(ui->m_d, &QTableView::activated, this, &CollateralEffectDialog::onIndexActivated);
    connect(ui->m_comment, &QTextEdit::textChanged, this, &CollateralEffectDialog::onCommentChanged);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

CollateralEffectDialog::~CollateralEffectDialog()
{
}

void CollateralEffectDialog::onIndexActivated(const QModelIndex &idx)
{
    auto idIdx = ui->m_d->model()->index(idx.row(), 1);

    m_selectedId = ui->m_d->model()->data(idIdx).toInt();

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_selectedId > 0);
}

void CollateralEffectDialog::onCommentChanged()
{
    m_comment = ui->m_comment->toPlainText();
}
