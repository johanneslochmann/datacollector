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
    moleculeclassmanagementwidget.cxx \
    moleculemanagementwidget.cxx \
    sexmanagementwidget.cxx \
    unitmanagementwidget.cxx \
    projectmanagementwidget.cxx \
    campaignmanagementwidget.cxx \
    probandmanagementwidget.cxx \
    dateeditdelegate.cxx \
    drugmanagementwidget.cxx \
    prescribeabledrugmanagmentwidget.cxx \
    prescribeabledrugcompositionmanagementwidget.cxx \
    prescriptiontypemanagementwidget.cxx \
    surveymanagementwidget.cxx

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
    moleculeclassmanagementwidget.hxx \
    moleculemanagementwidget.hxx \
    sexmanagementwidget.hxx \
    unitmanagementwidget.hxx \
    projectmanagementwidget.hxx \
    campaignmanagementwidget.hxx \
    probandmanagementwidget.hxx \
    dateeditdelegate.hxx \
    drugmanagementwidget.hxx \
    prescribeabledrugmanagmentwidget.hxx \
    prescribeabledrugcompositionmanagementwidget.hxx \
    prescriptiontypemanagementwidget.hxx \
    surveymanagementwidget.hxx

FORMS += \
    databaseconnectiondatadialog.ui
