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
    surveymanagementwidget.cxx \
    organizationunitmanagementwidget.cxx \
    icd10diagnosismanagementwidget.cxx \
    diagnosisinsurveymanagementwidget.cxx \
    surveydialog.cxx \
    storable.cxx \
    survey.cxx \
    project.cxx \
    abstractdatagateway.cxx \
    projectdatagateway.cxx \
    campaigndatagateway.cxx \
    campaign.cxx \
    proband.cxx \
    probanddatagateway.cxx \
    surveygateway.cxx \
    organization.cxx \
    organizationgateway.cxx \
    surveyform.cxx \
    plasmaticleveldialog.cxx \
    ondemanddrugdialog.cxx \
    regulardrugdialog.cxx \
    depotdrugdialog.cxx \
    icd10diagnosisdialog.cxx \
    corestatisticsform.cxx

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
    surveymanagementwidget.hxx \
    organizationunitmanagementwidget.hxx \
    icd10diagnosismanagementwidget.hxx \
    diagnosisinsurveymanagementwidget.hxx \
    surveydialog.hxx \
    storable.hxx \
    survey.hxx \
    project.hxx \
    abstractdatagateway.hxx \
    datagateway.h \
    projectdatagateway.hxx \
    campaigndatagateway.hxx \
    campaign.hxx \
    proband.hxx \
    probanddatagateway.hxx \
    surveygateway.hxx \
    organization.hxx \
    organizationgateway.hxx \
    surveyform.hxx \
    plasmaticleveldialog.hxx \
    ondemanddrugdialog.hxx \
    regulardrugdialog.hxx \
    depotdrugdialog.hxx \
    icd10diagnosisdialog.hxx \
    corestatisticsform.hxx

FORMS += \
    databaseconnectiondatadialog.ui \
    surveydialog.ui \
    surveyform.ui \
    plasmaticleveldialog.ui \
    ondemanddrugdialog.ui \
    regulardrugdialog.ui \
    depotdrugdialog.ui \
    icd10diagnosisdialog.ui \
    corestatisticsform.ui
