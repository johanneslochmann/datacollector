#pragma once

#include <QItemDelegate>

class DateEditDelegate: public QItemDelegate
{
public:
    explicit DateEditDelegate(QWidget *parent = 0);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex& index) const override;
};
