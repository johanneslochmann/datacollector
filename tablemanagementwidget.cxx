#include "tablemanagementwidget.hxx"

#include <QLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QLabel>
#include <QDataWidgetMapper>

#include "sqltablemodel.hxx"
#include "tableview.hxx"
#include "datacollector.hxx"

TableManagementWidget::TableManagementWidget(QWidget *parent, const QString &tableName, const QString& title)
    : QGroupBox(parent)
{
    setTitle(title);
    setLayout(new QHBoxLayout(this));

    m_model = new SqlTableModel(this, tableName);
    m_view = new TableView(this);
    m_view->setModel(m_model);
    m_view->setSelectionMode(QAbstractItemView::SingleSelection);
    m_view->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_model);

    layout()->addWidget(m_view);

    auto buttons = new QWidget(this);
    auto bl = new QVBoxLayout(buttons);
    buttons->setLayout(bl);
    layout()->addWidget(buttons);

    m_reload = new QPushButton(tr("&Reload"), buttons);
    m_abort = new QPushButton(tr("&Abort Changes"), buttons);
    m_save = new QPushButton(tr("&Save"), buttons);
    m_create = new QPushButton(tr("&Create"), buttons);
    m_delete = new QPushButton(tr("&Delete"), buttons);

    bl->addWidget(m_reload);
    bl->addWidget(m_abort);
    bl->addStretch();
    bl->addWidget(m_create);
    bl->addWidget(m_save);
    bl->addStretch();
    bl->addWidget(m_delete);

    connect(m_save, &QPushButton::clicked, this, &TableManagementWidget::save);
    connect(m_reload, &QPushButton::clicked, this, &TableManagementWidget::reload);
    connect(m_abort, &QPushButton::clicked, this, &TableManagementWidget::abort);
    connect(m_create, &QPushButton::clicked, this, &TableManagementWidget::create);
    connect(m_delete, &QPushButton::clicked, this, &TableManagementWidget::remove);

    connect(m_model, &QSqlTableModel::rowsInserted, this, &TableManagementWidget::onRowsInserted);

    // at this stage we assume to have a valid db connection
    reload(false);
}

void TableManagementWidget::reload(bool askUser)
{
    if (askUser) {
        if (QMessageBox::Yes != QMessageBox::question(this,
                                                      tr("Reload?"),
                                                      tr("Reload and loose all unsaved changes?"),
                                                      QMessageBox::Yes | QMessageBox::No)) {
            return;
        }
    }

    if (!m_model->select()) {
        QMessageBox::critical(this, tr("Failed to load data"),
                              tr("<p><b>Failed to load data:</b></p><p>%1\ndb:%2</p>")
                              .arg(m_model->lastError().text())
                              .arg(m_model->database().databaseName()));
    }
}

void TableManagementWidget::create()
{
    m_model->insertRows(m_model->rowCount(), 1);
}

void TableManagementWidget::abort()
{
    m_model->revertAll();
}

void TableManagementWidget::remove()
{
    auto selectedIndexes = m_view->selectionModel()->selectedRows(m_model->fieldIndex(nameColumnName()));

    if (selectedIndexes.empty()) {
        return;
    }

    if (1 != selectedIndexes.size()) {
        QMessageBox::information(this,
                                 tr("Usage Hint"),
                                 tr("<p>Select exactly one row.</p>"));
        return;
    }

    auto idx = selectedIndexes.first();

    if (QMessageBox::Yes != QMessageBox::warning(this,
                                                 tr("Delete Record?"),
                                                 tr("<p>Delete Record <i>%1</i> in row: %2?</p>")
                                                 .arg(m_model->data(idx).toString())
                                                 .arg(idx.row()),
                                                 QMessageBox::Yes | QMessageBox::No)) {
        return;
    }

    if (!m_model->removeRows(idx.row(), 1)) {
        QMessageBox::critical(this,
                              tr("Delete failed"),
                              tr("<p><b>Failed to delete data:</b></p><p>%1</p>")
                              .arg(m_model->lastError().text()));
    }

    save();
    reload(false);
}

void TableManagementWidget::save()
{
    if (!m_model->submitAll()) {
        QMessageBox::critical(this, tr("Failed to save data"),
                              tr("<p><b>Failed to save data:</b></p><p>%1</p>").arg(m_model->lastError().text()));
    }
}

void TableManagementWidget::onRowsInserted(const QModelIndex &parent, int first, int last)
{
    (void) parent;
    (void) first;
    (void) last;
    //reload(false);
}
