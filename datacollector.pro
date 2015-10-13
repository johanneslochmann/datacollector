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
    databaseerror.cxx

HEADERS  += mainwindow.hxx \
    datacollector.hxx \
    databaseconnectionawareaction.hxx \
    actionenabledifnotconnectedtodatabase.hxx \
    actionenabledifconnectedtodatabase.hxx \
    databaseconnectionstatuslabel.hxx \
    databaseconnectiondatadialog.hxx \
    databaseconnectiondata.hxx \
    settings.hxx \
    databaseerror.hxx

FORMS += \
    databaseconnectiondatadialog.ui
