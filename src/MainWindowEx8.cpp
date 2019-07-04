#include "MainWindowEx8.h"
#include <QDebug>


MainWindowEx8::MainWindowEx8()
{
    // resizes the main window
    resize(500, 300);

    // designs the interface

    // on the left
    m_leSearchField = new QLineEdit;
    m_pbSEARCH = new QPushButton("Search");

    m_vblLeftSide = new QVBoxLayout;
        m_vblLeftSide->addWidget(m_leSearchField);
        m_vblLeftSide->addWidget(m_pbSEARCH);
        m_vblLeftSide->addStretch(1);

    // on the right
    m_leName = new QLineEdit;
    m_leFirstName = new QLineEdit;

    m_leAge = new QLineEdit;
    m_ivAgeValidator = new QIntValidator(1,120);
    m_leAge->setValidator(m_ivAgeValidator);

    m_leSize = new QLineEdit;
    m_dvSizeValidator  = new QDoubleValidator(0.4,3.0, 2);
    m_leSize->setValidator(m_dvSizeValidator);

    m_leWeight = new QLineEdit;
    m_dvWeightValidator = new QDoubleValidator(2.5,250.0, 2);
    m_leWeight->setValidator(m_dvWeightValidator);

    m_formLayout = new QFormLayout;
        m_formLayout->addRow("Nom:",m_leName);
        m_formLayout->addRow("Prenom:",m_leFirstName);
        m_formLayout->addRow("Age:",m_leAge);
        m_formLayout->addRow("Taille (m):",m_leSize);
        m_formLayout->addRow("Poids (kg):",m_leWeight);

    m_pbADD = new QPushButton("ADD");
    m_pbRESET = new QPushButton("RESET");
    m_pbREMOVE = new QPushButton("REMOVE");

    m_vblRightSide = new QVBoxLayout;
        m_vblRightSide->addLayout(m_formLayout);
        m_vblRightSide->addWidget(m_pbADD);
        m_vblRightSide->addWidget(m_pbREMOVE);
        m_vblRightSide->addWidget(m_pbRESET);
        m_vblRightSide->addStretch(1);

    m_pMainLayout = new QHBoxLayout();
       m_pMainLayout->addLayout(m_vblLeftSide);
       m_pMainLayout->addLayout(m_vblRightSide);
	
    //=======Qt CONNECTIONS=========
    QObject::connect(m_pbSEARCH,    SIGNAL(clicked()), this,    SLOT(setSearchButton()));
    QObject::connect(m_pbRESET,     SIGNAL(clicked()), this,    SLOT(eraseSearchInfos()));
    QObject::connect(m_pbADD,       SIGNAL(clicked()), this,    SLOT(addPatient()));
    QObject::connect(m_pbREMOVE,    SIGNAL(clicked()), this,    SLOT(removePatient()));
   
    // attachs the layout to the main window
    setLayout(m_pMainLayout);

}

MainWindowEx8::~MainWindowEx8()
{
    if (nullptr != m_pbSEARCH)
        delete m_pbSEARCH;
     
    if (nullptr != m_leSearchField)
        delete m_leSearchField;

    if (nullptr != m_pbADD)
        delete m_pbADD;

    if (nullptr != m_pbREMOVE)
        delete m_pbREMOVE;

    if (nullptr != m_pbRESET)
        delete m_pbRESET;

    if (nullptr != m_formLayout)
        delete m_formLayout;

    if (nullptr != m_leName)
        delete m_leName;

    if (nullptr != m_leFirstName)
        delete m_leFirstName;

    if (nullptr != m_leAge)
        delete m_leAge;

    if (nullptr != m_ivAgeValidator)
        delete m_ivAgeValidator;

    if (nullptr != m_leSize)
        delete m_leSize;

    if (nullptr != m_dvSizeValidator)
        delete m_dvSizeValidator;

    if (nullptr != m_leWeight)
        delete m_leWeight;

    if (nullptr != m_dvWeightValidator)
        delete m_dvWeightValidator;

    if (nullptr != m_vblRightSide)
        delete m_vblRightSide;

    if (nullptr != m_vblLeftSide)
        delete m_vblLeftSide;
}

void MainWindowEx8::setSearchButton()
{
    emit sigBroadcastSearchField(m_leSearchField->text());
}

void MainWindowEx8::setSearchInfos(QString sName, QString sFirstName, int i32Age, float fSize, float fWeigth)
{
    m_leName->setText(sName);
    m_leFirstName->setText(sFirstName);
    m_leAge->setText(QString::number(i32Age));
    m_leSize->setText(QString::number(fSize));
    m_leWeight->setText(QString::number(fWeigth));
}

void MainWindowEx8::eraseSearchInfos()
{
    m_leSearchField->setText("");
    m_leName->setText("");
    m_leFirstName->setText("");
    m_leAge->setText("");
    m_leSize->setText("");
    m_leWeight->setText("");
}

void MainWindowEx8::addPatient()
{
    QLocale c(QLocale::French);
    bool ok;

    emit sigBroadcastAddPatient(m_leName->text(), m_leFirstName->text(), m_leAge->text().toInt(), c.toFloat(m_leSize->text(), &ok), c.toFloat(m_leWeight->text(), &ok));
}

void MainWindowEx8::removePatient()
{
    emit sigBroadcastRemovePatient(m_leName->text());
}
