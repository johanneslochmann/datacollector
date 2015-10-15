QT       += core gui sql
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = datacollector
TEMPLATE = app


SOURCES += main.cxx\
        mainwindow.cxx \
    datacollector.cxx \
    databaseconnectionawareaction.cxx \
    actionenabledifnotconnectedtodatabase.cxx \
    actionenabledifconnectedtodatabase.cxx \
    databaseconnectionstatuslabel.cxx \
    databaseconnectiondatadialog.cxx \
    databaseconnectiondata.cxx \
    settings.cxx \
    databaseerror.cxx \
    workbench.cxx \
    sqltablemodel.cxx \
    tablemanagementwidget.cxx \
    tableview.cxx \
    channelintopatientmanagementwidget.cxx \
    drugadministrationmethodmanagementwidget.cxx \
    moleculeclassmanagementwidget.cxx

HEADERS  += mainwindow.hxx \
    datacollector.hxx \
    databaseconnectionawareaction.hxx \
    actionenabledifnotconnectedtodatabase.hxx \
    actionenabledifconnectedtodatabase.hxx \
    databaseconnectionstatuslabel.hxx \
    databaseconnectiondatadialog.hxx \
    databaseconnectiondata.hxx \
    settings.hxx \
    databaseerror.hxx \
    workbench.hxx \
    sqltablemodel.hxx \
    tablemanagementwidget.hxx \
    tableview.hxx \
    channelintopatientmanagementwidget.hxx \
    drugadministrationmethodmanagementwidget.hxx \
    moleculeclassmanagementwidget.hxx

FORMS += \
    databaseconnectiondatadialog.ui
