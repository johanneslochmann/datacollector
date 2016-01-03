#include "crimecasewidget.hxx"

#include <QLayout>
#include <QGroupBox>
#include <QPushButton>

#include "crimecasestablewidget.hxx"
#include "crimecasedialog.hxx"

CrimeCaseWidget::CrimeCaseWidget(QWidget *parent) : QWidget(parent)
{
    setLayout(new QVBoxLayout(this));

    createCrimeCasesBox();
}

void CrimeCaseWidget::createCase()
{
    auto buf = std::make_shared<CrimeCase>();

    auto dlg = new CrimeCaseDialog(this, buf);

    if (QDialog::Accepted == dlg->exec()) {
        m_cases->reload();
        return;
    }

    m_cases->reload();
}

void CrimeCaseWidget::createCrimeCasesBox()
{
    auto b = new QGroupBox(tr("Crime Cases"), this);
    auto bl = new QHBoxLayout(b);

    b->setLayout(bl);

    m_cases = new CrimeCasesTableWidget(b);

    bl->addWidget(m_cases);
    m_reloadCases = new QPushButton(tr("&Reload"), b);
    m_createCase = new QPushButton(tr("&Create..."), b);
    m_editCase = new QPushButton(tr("&Edit..."), b);
    m_deleteCase = new QPushButton(tr("&Delete..."), b);

    auto l = new QVBoxLayout();
    l->addWidget(m_reloadCases);
    l->addStretch();
    l->addWidget(m_createCase);
    l->addWidget(m_editCase);
    l->addStretch();
    l->addWidget(m_deleteCase);

    bl->addItem(l);

    layout()->addWidget(b);

    connect(m_reloadCases, &QPushButton::clicked, m_cases, &CrimeCasesTableWidget::reload);
    connect(m_createCase, &QPushButton::clicked, this, &CrimeCaseWidget::createCase);
    connect(m_editCase, &QPushButton::clicked, m_cases, &CrimeCasesTableWidget::editSelected);
    connect(m_deleteCase, &QPushButton::clicked, m_cases, &CrimeCasesTableWidget::deleteSelected);
}
