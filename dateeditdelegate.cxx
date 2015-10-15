#include "dateeditdelegate.hxx"

#include <QDateTimeEdit>

DateEditDelegate::DateEditDelegate(QWidget *parent)
    : QItemDelegate(parent)
{
}

QWidget* DateEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    (void) option;
    QDateTimeEdit *e = new QDateTimeEdit(parent);

    e->setCalendarPopup(true);
    e->setDateTime(QDateTime::fromString(index.data().toString(), "dd/MM/yyyy hh:mm:ss"));
    e->setDisplayFormat("dd/mm/yyyy");
    return e;
}

void DateEditDelegate::setEditorData(QWidget *paramEditor, const QModelIndex &index) const
{
    QDateTimeEdit *editor = qobject_cast<QDateTimeEdit *>(paramEditor);

    editor->setDateTime(QDateTime::fromString(index.data().toString(), "dd/MM/yyyy hh:mm:ss"));
}

void DateEditDelegate::setModelData(QWidget *paramEditor, QAbstractItemModel *model, const QModelIndex& index) const
{
    QDateTimeEdit *editor = qobject_cast<QDateTimeEdit *>(paramEditor);

    model->setData(index, editor->dateTime().toString("dd/MM/yyyy hh:mm:ss"));
}
