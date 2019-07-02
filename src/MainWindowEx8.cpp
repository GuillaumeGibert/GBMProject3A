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
    QObject::connect(m_pbSEARCH, SIGNAL(clicked()), this,    SLOT(setSearchButton()));
   
    // attachs the layout to the main window
    setLayout(m_pMainLayout);

}

MainWindowEx8::~MainWindowEx8()
{
    if (nullptr != m_pbSEARCH)
     delete m_pbSEARCH;
     
   
}

void MainWindowEx8::setSearchButton()
{
    emit sigBroadcastSearchField(m_leSearchField->text());
}


