#include "MainWindowEx7.h"
#include <QDebug>


MainWindowEx7::MainWindowEx7()
{
    // resizes the main window
    resize(300, 500);

    // designs the interface
    m_pStartButton = new QPushButton("Start");
    m_pStopButton = new QPushButton("Stop");
	
    m_pMainLayout = new QHBoxLayout();
        m_pMainLayout->addWidget(m_pStartButton);
	m_pMainLayout->addWidget(m_pStopButton);

     //=======Qt CONNECTIONS=========
    QObject::connect(m_pStartButton, SIGNAL(clicked()), this,    SLOT(setStartButton()));
    QObject::connect(m_pStopButton, SIGNAL(clicked()), this,    SLOT(setStopButton()));

    // attachs the layout to the main window
    setLayout(m_pMainLayout);

}

MainWindowEx7::~MainWindowEx7()
{
     if (nullptr != m_pStartButton)
        delete m_pStartButton;
     
     if (nullptr != m_pStopButton)
        delete m_pStopButton;
}

void MainWindowEx7::setStartButton()
{
    QByteArray l_oButtonPressed = "Start\n";
	emit sigSendButtonPressed(l_oButtonPressed);
}

void MainWindowEx7::setStopButton()
{
    QByteArray l_oButtonPressed = "Stop\n";
	emit sigSendButtonPressed(l_oButtonPressed);
}

