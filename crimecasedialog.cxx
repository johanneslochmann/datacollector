#include "crimecasedialog.hxx"

#include <QDialogButtonBox>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QGroupBox>
#include <QFormLayout>
#include <QPushButton>

#include "datacollector.hxx"
#include "crimecasegateway.hxx"
#include "housingtypecombobox.hxx"
#include "citycombobox.hxx"
#include "crimecaseparticipanttablewidget.hxx"
#include "informationsourceforcrimecasetablewidget.hxx"
#include "informationsourceforcrimecasedialog.hxx"

CrimeCaseDialog::CrimeCaseDialog(QWidget *p, CrimeCaseSPtr d)
    : QDialog(p), m_crimeCase(d)
{
    setLayout(new QVBoxLayout(this));

    createWidgets();
}

CrimeCaseDialog::~CrimeCaseDialog()
{
}

void CrimeCaseDialog::accept()
{
    if (CrimeCaseGateway().save(m_crimeCase)) {
        done(QDialog::Accepted);
    }
}

void CrimeCaseDialog::save()
{
    if (CrimeCaseGateway().save(m_crimeCase)) {
        emit crimeCaseSaved();
    }
}

void CrimeCaseDialog::createParticipant()
{

}

void CrimeCaseDialog::createInformationSource()
{
    auto buf = std::make_shared<InformationSourceForCrimeCase>();
    buf->setCrimeCase(m_crimeCase);

    auto dlg = new InformationSourceForCrimeCaseDialog(this, buf);

    if (QDialog::Accepted == dlg->exec()) {
        m_informationSources->reload();
    }
}

void CrimeCaseDialog::onCrimeCaseSaved()
{
    m_participantsBox->setEnabled(true);
    m_informationSourcesBox->setEnabled(true);

    m_participants->onCrimeCaseChanged(m_crimeCase);
    m_informationSources->setCrimeCase(m_crimeCase);
}

void CrimeCaseDialog::createWidgets()
{
    m_mainBox = new QGroupBox(tr("Crime Case"), this);
    m_mainBox->setLayout(new QGridLayout(m_mainBox));

    createCoreInfoBox();
    createInformationSourcesBox();
    createParticipantsBox();

    m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Save,
                                     Qt::Horizontal,
                                     this);

    layout()->addWidget(m_mainBox);
    layout()->addWidget(m_buttons);

    connect(m_buttons, &QDialogButtonBox::rejected, this, &CrimeCaseDialog::reject);
    connect(m_buttons->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &CrimeCaseDialog::accept);
    connect(m_buttons->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &CrimeCaseDialog::save);

    m_participantsBox->setEnabled(false);
    m_informationSourcesBox->setEnabled(false);

    connect(this, &CrimeCaseDialog::crimeCaseSaved, this, &CrimeCaseDialog::onCrimeCaseSaved);

    if (m_crimeCase->id() > 0) {
        emit crimeCaseSaved();
    }
}

void CrimeCaseDialog::createCoreInfoBox()
{
    m_coreInfoBox = new QGroupBox(tr("Core Information"), m_mainBox);
    auto l = new QFormLayout(m_coreInfoBox);
    m_coreInfoBox->setLayout(l);

    m_name = new QLineEdit(m_crimeCase->name(), m_coreInfoBox);
    m_crimeYear = new QLineEdit(m_crimeCase->crimeYear().toString(), m_coreInfoBox);
    m_crimeDate = new QLineEdit(m_crimeCase->crimeDate().toString(), m_coreInfoBox);
    m_crimeTime = new QLineEdit(m_crimeCase->crimeTime().toString(), m_coreInfoBox);
    m_housingType = new HousingTypeComboBox(m_coreInfoBox);
    m_city = new CityComboBox(m_coreInfoBox);
    m_description = new QTextEdit(m_crimeCase->description(), m_coreInfoBox);

    l->addRow(tr("&Name"), m_name);
    l->addRow(tr("&Year"), m_crimeYear);
    l->addRow(tr("&Date [YYYY-MM-DD]"), m_crimeDate);
    l->addRow(tr("&Time [h:m]"), m_crimeTime);
    l->addRow(tr("&Housing Type"), m_housingType);
    l->addRow(tr("&City"), m_city);
    l->addRow(tr("D&escription"), m_description);

    m_housingType->reload();
    m_city->reload();

    if (m_crimeCase->housingType()->id() > 0) {
        m_housingType->setCurrentText(m_crimeCase->housingType()->name());
    }

    if (m_crimeCase->city()->id() > 0) {
        m_city->setCurrentText(m_crimeCase->city()->name());
    }

    m_mainBox->layout()->addWidget(m_coreInfoBox);

    connect(m_name, &QLineEdit::textChanged, [=](const QString& s) { m_crimeCase->setName(s); });
    connect(m_crimeYear, &QLineEdit::textChanged, [=](const QString& s) { m_crimeCase->setCrimeYear(s.toInt()); });
    connect(m_crimeDate, &QLineEdit::textChanged, [=](const QString& s) { m_crimeCase->setCrimeDate(QDate::fromString(s, Qt::ISODate)); });
    connect(m_crimeTime, &QLineEdit::textChanged, [=](const QString& s) { m_crimeCase->setCrimeTime(QTime::fromString(s, "h:m")); });
    connect(m_description, &QTextEdit::textChanged, [=]() { m_crimeCase->setDescription(m_description->toPlainText()); });
    connect(m_housingType, &HousingTypeComboBox::currentHousingTypeChanged, [=](HousingTypeSPtr t) { m_crimeCase->setHousingType(t); });
    connect(m_city, &CityComboBox::currentCityChanged, [=](CitySPtr c) { m_crimeCase->setCity(c); });
}

void CrimeCaseDialog::createParticipantsBox()
{
    m_participantsBox = new QGroupBox(tr("&Participants"), m_coreInfoBox);
    m_participantsBox->setLayout(new QHBoxLayout(m_participantsBox));

    m_participants = new CrimeCaseParticipantTableWidget(m_participantsBox);
    m_participantsBox->layout()->addWidget(m_participants);
    m_participants->onCrimeCaseChanged(m_crimeCase);

    m_reloadParticipants = new QPushButton(tr("&Reload"), m_participantsBox);
    m_createParticipant = new QPushButton(tr("&Create..."), m_participantsBox);
    m_editParticipant = new QPushButton(tr("&Edit..."), m_participantsBox);
    m_deleteParticipant = new QPushButton(tr("&Delete..."), m_participantsBox);

    QVBoxLayout* m_bl = new QVBoxLayout();
    m_bl->addWidget(m_reloadParticipants);
    m_bl->addStretch();
    m_bl->addWidget(m_createParticipant);
    m_bl->addWidget(m_editParticipant);
    m_bl->addStretch();
    m_bl->addWidget(m_deleteParticipant);

    m_participantsBox->layout()->addItem(m_bl);
    m_mainBox->layout()->addWidget(m_participantsBox);

    connect(m_reloadParticipants, &QPushButton::clicked, m_participants, &CrimeCaseParticipantTableWidget::reload);
    connect(m_createParticipant, &QPushButton::clicked, this, &CrimeCaseDialog::createParticipant);
    connect(m_editParticipant, &QPushButton::clicked, m_participants, &CrimeCaseParticipantTableWidget::editSelected);
    connect(m_deleteParticipant, &QPushButton::clicked, m_participants, &CrimeCaseParticipantTableWidget::deleteSelected);
}

void CrimeCaseDialog::createInformationSourcesBox()
{
    m_informationSourcesBox = new QGroupBox(tr("&Information Sources"), m_mainBox);
    m_informationSourcesBox->setLayout(new QHBoxLayout(m_informationSourcesBox));

    m_informationSources = new InformationSourceForCrimeCaseTableWidget(m_informationSourcesBox);
    m_informationSources->setCrimeCase(m_crimeCase);
    m_informationSourcesBox->layout()->addWidget(m_informationSources);

    m_reloadInformationSources = new QPushButton(tr("&Reload"), m_informationSourcesBox);
    m_createInformationSource = new QPushButton(tr("&Create..."), m_informationSourcesBox);
    m_editInformationSource = new QPushButton(tr("&Edit..."), m_informationSourcesBox);
    m_deleteInformationSource = new QPushButton(tr("&Delete..."), m_informationSourcesBox);

    auto bl = new QVBoxLayout();
    bl->addWidget(m_reloadInformationSources);
    bl->addStretch();
    bl->addWidget(m_createInformationSource);
    bl->addWidget(m_editInformationSource);
    bl->addStretch();
    bl->addWidget(m_deleteInformationSource);

    m_informationSourcesBox->layout()->addItem(bl);
    m_mainBox->layout()->addWidget(m_informationSourcesBox);

    connect(m_reloadInformationSources, &QPushButton::clicked, m_informationSources, &InformationSourceForCrimeCaseTableWidget::reload);
    connect(m_createInformationSource, &QPushButton::clicked, this, &CrimeCaseDialog::createInformationSource);
    connect(m_editInformationSource, &QPushButton::clicked, m_informationSources, &InformationSourceForCrimeCaseTableWidget::editSelected);
    connect(m_deleteInformationSource, &QPushButton::clicked, m_informationSources, &InformationSourceForCrimeCaseTableWidget::deleteSelected);
}
