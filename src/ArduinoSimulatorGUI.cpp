#include "ArduinoSimulatorGUI.h"

ArduinoSimulatorGUI::ArduinoSimulatorGUI()
{
        setFixedSize(200, 200);
        m_pLoadConfigFileButton = new QPushButton("Load Data", this);
        QObject::connect(m_pLoadConfigFileButton, SIGNAL(clicked()), this, SLOT(openDialog()));
}

ArduinoSimulatorGUI::~ArduinoSimulatorGUI()
{
    if (nullptr != m_pLoadConfigFileButton)
    {
        delete m_pLoadConfigFileButton;
        m_pLoadConfigFileButton = nullptr;
    }
}

void ArduinoSimulatorGUI::openDialog()
{
    QString sDataFilename = QFileDialog::getOpenFileName(this, "Load Data", QString(), "data(*.txt)");

    if (!sDataFilename.isEmpty())
        emit sendDataFilename(sDataFilename);
}

