#include "plasmaticleveldialog.hxx"

#include <QComboBox>
#include <QTextEdit>

#include "ui_plasmaticleveldialog.h"

#include "datacollector.hxx"

PlasmaticLevelDialog::PlasmaticLevelDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::unique_ptr<Ui::PlasmaticLevelDialog>(new Ui::PlasmaticLevelDialog))
{
    ui->setupUi(this);

    ui->m_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->m_data->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->concentration->setValidator(new QDoubleValidator(this));

    connect(ui->concentration, &QLineEdit::textChanged, this, &PlasmaticLevelDialog::onValueChanged);
    connect(ui->units, SIGNAL(activated(QString)), this, SLOT(onUnitActivated(QString)));
    connect(ui->comment, &QTextEdit::textChanged, this, &PlasmaticLevelDialog::onCommentChanged);

    m_moleculeModel = new QSqlQueryModel(this);
    m_unitModel = new QSqlQueryModel(this);

    try {
        m_moleculeQry = DataCollector::get()->prepareAndPerformQuery("select "
                                                                     "m.name as name, m.id as id "
                                                                     "from core.molecule m "
                                                                     "order by name asc;", false);
        m_unitQry = DataCollector::get()->prepareAndPerformQuery("select name from core.unit order by name asc;", false);

        m_unitModel->setQuery(m_unitQry);
        m_moleculeModel->setQuery(m_moleculeQry);

        ui->m_data->setModel(m_moleculeModel);
        ui->m_data->hideColumn(1);

        ui->units->setModel(m_unitModel);

        ui->units->setCurrentText(m_unitName);
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load Prescribeable Drug list."), this);
    }

    connect(ui->m_data, &QTableView::activated, this, &PlasmaticLevelDialog::onIndexActivated);
}

PlasmaticLevelDialog::~PlasmaticLevelDialog()
{
}

void PlasmaticLevelDialog::onUnitActivated(const QString &txt)
{
    m_unitName = txt;
}

void PlasmaticLevelDialog::onValueChanged(const QString &txt)
{
    m_value = txt.toDouble();
}

void PlasmaticLevelDialog::onCommentChanged()
{
    m_comment = ui->comment->toPlainText();
}

void PlasmaticLevelDialog::onIndexActivated(const QModelIndex &idx)
{
    auto idIdx = ui->m_data->model()->index(idx.row(), 1);

    m_selectedId = ui->m_data->model()->data(idIdx).toInt();
}
