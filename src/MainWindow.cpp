#include "MainWindow.h"
#include <QDebug>

#define FPS 100.0

MainWindow::MainWindow() :
    m_pSignalDisplay(nullptr),
    m_pFilteredSignalDisplay(nullptr),
    m_pBufferedSignalDisplay(nullptr),
    m_pPowerSpectrumDisplay(nullptr),
    m_pMainLayout(nullptr),
    m_pSignalLayout(nullptr),
    m_pMainVLayout(nullptr)
{

}

MainWindow::~MainWindow()
{
    if (nullptr != m_pSignalDisplay)
        delete m_pSignalDisplay;

    if (nullptr != m_pFilteredSignalDisplay)
        delete m_pFilteredSignalDisplay;

    if (nullptr != m_pBufferedSignalDisplay)
        delete m_pBufferedSignalDisplay;

    if (nullptr != m_pPowerSpectrumDisplay)
        delete m_pPowerSpectrumDisplay;

    if (nullptr != m_pMainLayout)
        delete m_pMainLayout;

    if (nullptr != m_pSignalLayout)
        delete m_pSignalLayout;

    if (nullptr != m_pMainVLayout)
        delete m_pMainVLayout;

}

void MainWindow::setSignalValues(float timestamp, std::vector<float> vSignalValues)
{
    m_pSignalDisplay->setNewValues(vSignalValues);
}

void MainWindow::setFilteredSignalValues(std::vector<float> vFilteredSignalValues)
{
    m_pFilteredSignalDisplay->setNewValues(vFilteredSignalValues);
}

void MainWindow::setBufferedSignalValues(std::vector<std::deque<float>> vBufferedSignalValues)
{
    m_pBufferedSignalDisplay->setNewValues(vBufferedSignalValues);
}

void MainWindow::setPowerSpectrumValues(std::vector<std::deque<float>> vBufferedSignalValues)
{
    m_pPowerSpectrumDisplay->setNewValues(vBufferedSignalValues);
}

