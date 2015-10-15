#include "channelintopatientmanagementwidget.hxx"

#include "tableview.hxx"
#include "sqltablemodel.hxx"

ChannelIntoPatientManagementWidget::ChannelIntoPatientManagementWidget(QWidget *p)
    : TableManagementWidget(p, "core.channel_into_patient", QObject::tr("Channels Into Patient"))
{
    view()->hideColumn(model()->fieldIndex("id")); // hide id column
    model()->select();
}

