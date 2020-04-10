#include "MainWindowEx9.h"
#include <QDebug>

#define FPS 10.0

MainWindowEx9::MainWindowEx9()
{
    // creates a display for input signals
    m_pSignalDisplay = new TemporalSignalDisplay();
        m_pSignalDisplay->setWidgetSize(QSize(320, 240));
        std::vector<std::string> vSignalLabels;
        vSignalLabels.push_back("1");vSignalLabels.push_back("2");vSignalLabels.push_back("3");vSignalLabels.push_back("4");vSignalLabels.push_back("5");
        m_pSignalDisplay->setSignalLabels(vSignalLabels);
        m_pSignalDisplay->setFps(FPS); // watch out fps must be set before setting XY range AND must be the same than the retrieved signals (from serial port or sine generator)
        m_pSignalDisplay->setXYRange(QSize(0, 20), QSize(250, 350)); // for arduino if nothing connected to analogic inputs (A0..A5)
        m_pSignalDisplay->setXYRange(QSize(0, 2), QSize(-60, 60)); // for the sine generator
        m_pSignalDisplay->setLegends("Time (s)", "Signal (V)");
        m_pSignalDisplay->setTicks(1, 5);
        m_pSignalDisplay->setDrawLine(true);

    // creates a button to start searching the Bt server
    m_pSearchBtServer = new QPushButton;
    m_pSearchBtServer->setText("Search");
    QObject::connect(m_pSearchBtServer, SIGNAL(clicked()), this, SLOT(searchBtServerClicked()));

    // creates a button to quit
    m_pQuit = new QPushButton;
    m_pQuit->setText("Quit");
    QObject::connect(m_pQuit, SIGNAL(clicked()), this, SLOT(quitInterface()));

    // designs the interface
    m_pMainVLayout = new QVBoxLayout();
        m_pMainVLayout->addWidget(m_pSignalDisplay);
        m_pMainVLayout->addWidget(m_pSearchBtServer);
        m_pMainVLayout->addWidget(m_pQuit);

    // attachs the layout to the main window
    setLayout(m_pMainVLayout);

}

MainWindowEx9::~MainWindowEx9()
{
    if (nullptr != m_pQuit)
        delete m_pQuit;

    if (nullptr != m_pSearchBtServer)
        delete m_pSearchBtServer;
}

void MainWindowEx9::searchBtServerClicked()
{
    emit searchBtServer();
}

void MainWindowEx9::quitInterface()
{
    emit quit();
}


