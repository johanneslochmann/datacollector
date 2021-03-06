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
    corestatisticsform.cxx \
    ageclassmanagementwidget.cxx \
    smokinghabitsmanagementwidget.cxx \
    smokinghabit.cxx \
    smokinghabitgateway.cxx \
    collateraleffectmanagementwidget.cxx \
    collateraleffectdialog.cxx \
    cgidialog.cxx \
    gafdialog.cxx \
    fpsdialog.cxx \
    whoqoldialog.cxx \
    agaterecord.cxx \
    agateform.cxx \
    datacombobox.cxx \
    projectcombobox.cxx \
    manualagatewidget.cxx \
    filtereddatacombobox.cxx \
    campaigncombobox.cxx \
    datatablewidget.cxx \
    agatesurveystablewidget.cxx \
    agaterecordgateway.cxx \
    sex.cxx \
    sexcombobox.cxx \
    sexdatagateway.cxx \
    agaterecorddialog.cxx \
    organizationcombobox.cxx \
    agatedepottablewidget.cxx \
    agatedepotdialog.cxx \
    nameidpair.cxx \
    prescribeabledruggateway.cxx \
    agatemedicationtablewidget.cxx \
    agatemedicationdialog.cxx \
    moleculegateway.cxx \
    agatediagnosistablewidget.cxx \
    agatediagnosisdialog.cxx \
    diagnosisgateway.cxx \
    htmlviewer.cxx \
    agaterecordviewer.cxx \
    countrymanagementwidget.cxx \
    weapontypemanagementwidget.cxx \
    housingtypemanagementwidget.cxx \
    modusoperandimanagementwidget.cxx \
    crimetypemanagementwidget.cxx \
    informationsourcetypemanagementwidget.cxx \
    crimecasepartyrolemanagementwidget.cxx \
    jobmanagementwidget.cxx \
    crimemotivemanagementwidget.cxx \
    mentaldiseasemanagementwidget.cxx \
    consultancyresultmanagementwidget.cxx \
    weaponmanagementwidget.cxx \
    citymanagementwidget.cxx \
    crimecase.cxx \
    crimecasegateway.cxx \
    crimecasewidget.cxx \
    crimecasestablewidget.cxx \
    crimecasedialog.cxx \
    housingtypecombobox.cxx \
    housingtype.cxx \
    housingtypegateway.cxx \
    city.cxx \
    citygateway.cxx \
    citycombobox.cxx \
    informationsourceforcrimecase.cxx \
    informationsourcetype.cxx \
    informationsourcetypegateway.cxx \
    informationsourcetypecombobox.cxx \
    crimecasecombobox.cxx \
    crimecaseparticipanttablewidget.cxx \
    crimecaseparticipant.cxx \
    crimecaseparticipantgateway.cxx \
    informationsourceforcrimecasetablewidget.cxx \
    informationsourceforcrimecasegateway.cxx \
    informationsourceforcrimecasedialog.cxx \
    crimecaseparticipantdialog.cxx \
    crimecasepartyrole.cxx \
    crimecasepartyrolegateway.cxx \
    crimecasepartyrolecombobox.cxx \
    crimetype.cxx \
    crimetypegateway.cxx \
    crimetypecombobox.cxx \
    job.cxx \
    jobgateway.cxx \
    jobcombobox.cxx \
    crimemotive.cxx \
    crimemotivegateway.cxx \
    crimemotivecombobox.cxx \
    mentaldisease.cxx \
    mentaldiseasegateway.cxx \
    mentaldiseasecombobox.cxx \
    modusoperandi.cxx \
    modusoperandigateway.cxx \
    modusoperandicombobox.cxx \
    weapon.cxx \
    weapongateway.cxx \
    weaponcombobox.cxx \
    consultancyresult.cxx \
    consultancyresultgateway.cxx \
    consultancyresultcombobox.cxx \
    processingstatus.cxx \
    processingstatusgateway.cxx \
    processingstatuscombobox.cxx \
    processingstatusmanagementwidget.cxx \
    aboutdatacollectordialog.cxx \
    settingsdialog.cxx \
    filenameselector.cxx

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
    corestatisticsform.hxx \
    ageclassmanagementwidget.hxx \
    smokinghabitsmanagementwidget.hxx \
    smokinghabit.hxx \
    smokinghabitgateway.hxx \
    collateraleffectmanagementwidget.hxx \
    collateraleffectdialog.hxx \
    cgidialog.hxx \
    gafdialog.hxx \
    fpsdialog.hxx \
    whoqoldialog.hxx \
    agaterecord.hxx \
    agateform.hxx \
    datacombobox.hxx \
    projectcombobox.hxx \
    manualagatewidget.hxx \
    filtereddatacombobox.hxx \
    campaigncombobox.hxx \
    datatablewidget.hxx \
    agatesurveystablewidget.hxx \
    agaterecordgateway.hxx \
    sex.hxx \
    sexcombobox.hxx \
    sexdatagateway.hxx \
    agaterecorddialog.hxx \
    organizationcombobox.hxx \
    agatedepottablewidget.hxx \
    agatedepotdialog.hxx \
    nameidpair.hxx \
    prescribeabledruggateway.hxx \
    agatemedicationtablewidget.hxx \
    agatemedicationdialog.hxx \
    moleculegateway.hxx \
    agatediagnosistablewidget.hxx \
    agatediagnosisdialog.hxx \
    diagnosisgateway.hxx \
    htmlviewer.hxx \
    agaterecordviewer.hxx \
    countrymanagementwidget.hxx \
    weapontypemanagementwidget.hxx \
    housingtypemanagementwidget.hxx \
    modusoperandimanagementwidget.hxx \
    crimetypemanagementwidget.hxx \
    informationsourcetypemanagementwidget.hxx \
    crimecasepartyrolemanagementwidget.hxx \
    jobmanagementwidget.hxx \
    crimemotivemanagementwidget.hxx \
    mentaldiseasemanagementwidget.hxx \
    consultancyresultmanagementwidget.hxx \
    weaponmanagementwidget.hxx \
    citymanagementwidget.hxx \
    crimecase.hxx \
    crimecasegateway.hxx \
    crimecasewidget.hxx \
    crimecasestablewidget.hxx \
    crimecasedialog.hxx \
    housingtypecombobox.hxx \
    housingtype.hxx \
    housingtypegateway.hxx \
    city.hxx \
    citygateway.hxx \
    citygateway.cxx \
    citycombobox.hxx \
    informationsourceforcrimecase.hxx \
    informationsourcetype.hxx \
    informationsourcetypegateway.hxx \
    informationsourcetypecombobox.hxx \
    crimecasecombobox.hxx \
    crimecaseparticipanttablewidget.hxx \
    crimecaseparticipant.hxx \
    crimecaseparticipantgateway.hxx \
    informationsourceforcrimecasetablewidget.hxx \
    informationsourceforcrimecasegateway.hxx \
    informationsourceforcrimecasedialog.hxx \
    crimecaseparticipantdialog.hxx \
    crimecasepartyrole.hxx \
    crimecasepartyrolegateway.hxx \
    crimecasepartyrolecombobox.hxx \
    crimetype.hxx \
    crimetypegateway.hxx \
    crimetypecombobox.hxx \
    job.hxx \
    jobgateway.hxx \
    jobcombobox.hxx \
    crimemotive.hxx \
    crimemotivegateway.hxx \
    crimemotivecombobox.hxx \
    mentaldisease.hxx \
    mentaldiseasegateway.hxx \
    mentaldiseasecombobox.hxx \
    modusoperandi.hxx \
    modusoperandigateway.hxx \
    modusoperandicombobox.hxx \
    weapon.hxx \
    weapongateway.hxx \
    weaponcombobox.hxx \
    consultancyresult.hxx \
    consultancyresultgateway.hxx \
    consultancyresultcombobox.hxx \
    processingstatus.hxx \
    processingstatusgateway.hxx \
    processingstatuscombobox.hxx \
    processingstatusmanagementwidget.hxx \
    aboutdatacollectordialog.hxx \
    settingsdialog.hxx \
    filenameselector.hxx

FORMS += \
    databaseconnectiondatadialog.ui \
    surveydialog.ui \
    surveyform.ui \
    plasmaticleveldialog.ui \
    ondemanddrugdialog.ui \
    regulardrugdialog.ui \
    depotdrugdialog.ui \
    icd10diagnosisdialog.ui \
    corestatisticsform.ui \
    collateraleffectdialog.ui \
    cgidialog.ui \
    gafdialog.ui \
    fpsdialog.ui \
    whoqoldialog.ui \
    agateform.ui \
    aboutdatacollectordialog.ui

 TRANSLATIONS = \
    datacollector.de_DE.ts \
    datacollector.it_IT.ts

RESOURCES += \
    resources.qrc

DISTFILES += \
    crebas.sql
