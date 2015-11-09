#include "datatablewidget.hxx"

DataTableWidget::DataTableWidget(QWidget *p)
    : QTableWidget(p)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

