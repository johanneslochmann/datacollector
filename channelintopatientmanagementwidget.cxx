#include "channelintopatientmanagementwidget.hxx"

#include "tableview.hxx"
#include "sqltablemodel.hxx"

ChannelIntoPatientManagementWidget::ChannelIntoPatientManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.channel_into_patient", QObject::tr("Channels Into Patient"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column

    model()->setHeaderData(model()->fieldIndex("name"), Qt::Horizontal, tr("Name"));
    model()->setHeaderData(model()->fieldIndex("description"), Qt::Horizontal, tr("Description"));

    model()->select();
}

