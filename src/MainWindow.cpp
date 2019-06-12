#include "MainWindow.h"
#include <QDebug>

#define FPS 100.0

MainWindow::MainWindow()
{
    // creates a display for input signals
    m_pSignalDisplay = new TemporalSignalDisplay();
        m_pSignalDisplay->setWidgetSize(QSize(640, 480));
        std::vector<std::string> vSignalLabels;
        vSignalLabels.push_back("1");vSignalLabels.push_back("2");vSignalLabels.push_back("3");vSignalLabels.push_back("4");vSignalLabels.push_back("5");
        m_pSignalDisplay->setSignalLabels(vSignalLabels);
        m_pSignalDisplay->setFps(FPS); // watch out fps must be set before setting XY range AND must be the same than the retrieved signals (from serial port or sine generator)
        m_pSignalDisplay->setXYRange(QSize(0, 20), QSize(250, 350)); // for arduino if nothing connected to analogic inputs (A0..A5)
        m_pSignalDisplay->setXYRange(QSize(0, 2), QSize(-60, 60)); // for the sine generator
        m_pSignalDisplay->setLegends("Time (s)", "Signal (V)");
        m_pSignalDisplay->setTicks(1, 5);
        m_pSignalDisplay->setDrawLine(true);

    // creates a display for filtered signals
    m_pFilteredSignalDisplay = new TemporalSignalDisplay();
        m_pFilteredSignalDisplay->setWidgetSize(QSize(640, 480));
        m_pFilteredSignalDisplay->setSignalLabels(vSignalLabels);
        m_pFilteredSignalDisplay->setFps(FPS); // watch out fps must be set before setting XY range AND must be the same than the retrieved signals (from serial port or sine generator)
        m_pFilteredSignalDisplay->setXYRange(QSize(0, 20), QSize(250, 350)); // for arduino if nothing connected to analogic inputs (A0..A5)
        m_pFilteredSignalDisplay->setXYRange(QSize(0, 2), QSize(-60, 60)); // for the sine generator
        m_pFilteredSignalDisplay->setLegends("Time (s)", "Signal (V)");
        m_pFilteredSignalDisplay->setTicks(1, 5);
        m_pFilteredSignalDisplay->setDrawLine(true);

    // creates a display for filtered signals
    m_pBufferedSignalDisplay = new BufferedSignalDisplay();
        m_pBufferedSignalDisplay->setWidgetSize(QSize(640, 480));
        m_pBufferedSignalDisplay->setSignalLabels(vSignalLabels);
        m_pBufferedSignalDisplay->setFps(FPS); // watch out fps must be set before setting XY range AND must be the same than the retrieved signals (from serial port or sine generator)
        m_pBufferedSignalDisplay->setXYRange(QSize(0, 20), QSize(250, 350)); // for arduino if nothing connected to analogic inputs (A0..A5)
        m_pBufferedSignalDisplay->setXYRange(QSize(0, 2), QSize(-60, 60)); // for the sine generator
        m_pBufferedSignalDisplay->setLegends("Time (s)", "Signal (V)");
        m_pBufferedSignalDisplay->setTicks(1, 5);
        m_pBufferedSignalDisplay->setDrawLine(true);

    // creates a display for power spectrum
    m_pPowerSpectrumDisplay = new BufferedSignalDisplay();
        m_pPowerSpectrumDisplay->setWidgetSize(QSize(640, 480));
        m_pPowerSpectrumDisplay->setSignalLabels(vSignalLabels);
        m_pPowerSpectrumDisplay->setFps(FPS); // watch out fps must be set before setting XY range AND must be the same than the retrieved signals (from serial port or sine generator)
        m_pPowerSpectrumDisplay->setXYRange(QSize(0, 20), QSize(250, 350)); // for arduino if nothing connected to analogic inputs (A0..A5)
        m_pPowerSpectrumDisplay->setXYRange(QSize(-50, 50), QSize(0, 2)); // for the sine generator
        m_pPowerSpectrumDisplay->setLegends("Frequency (Hz)", "Power Spectrum");
        m_pPowerSpectrumDisplay->setTicks(1, 5);
        m_pPowerSpectrumDisplay->setDrawLine(true);

    // creates an array of checkboxes to enabe/disable the display of specific signals
    QGroupBox *groupBoxSignal = new QGroupBox("Signal");
    QVBoxLayout *vboxSignal = new QVBoxLayout;
    std::vector<QCheckBox*> vSignalCheckBoxes;

    for (int l_cb = 0; l_cb < static_cast<int>(vSignalLabels.size()); l_cb++)
    {
        QCheckBox* l_ocb = new QCheckBox(QString::fromStdString(vSignalLabels[static_cast<unsigned long long>(l_cb)]));
        l_ocb->setChecked(true);
        l_ocb->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        vboxSignal->addWidget(l_ocb);
        vSignalCheckBoxes.push_back(l_ocb);
    }
    vboxSignal->addStretch(1);
    groupBoxSignal->setFixedWidth(100);
    groupBoxSignal->setLayout(vboxSignal);

    // connects check box signals to enable/disable display via a signal mapper
    QSignalMapper* sigMapper = new QSignalMapper;
    for (int l_cb = 0; l_cb < static_cast<int>(vSignalLabels.size()); l_cb++)
    {
        QObject::connect(vSignalCheckBoxes[static_cast<unsigned long long>(l_cb)], SIGNAL(stateChanged(int)), sigMapper, SLOT(map()));
        sigMapper->setMapping(vSignalCheckBoxes[static_cast<unsigned long long>(l_cb)], l_cb);
    }
    QObject::connect(sigMapper, SIGNAL(mapped(int)), m_pSignalDisplay,          SLOT(setSignalEnabled(int)));
    QObject::connect(sigMapper, SIGNAL(mapped(int)), m_pFilteredSignalDisplay,  SLOT(setSignalEnabled(int)));
    QObject::connect(sigMapper, SIGNAL(mapped(int)), m_pBufferedSignalDisplay,  SLOT(setSignalEnabled(int)));
    QObject::connect(sigMapper, SIGNAL(mapped(int)), m_pPowerSpectrumDisplay,   SLOT(setSignalEnabled(int)));

    // resizes the main window
    resize(1800, 1000);

    // designs the interface
    m_pSignalLayout = new QHBoxLayout();
        m_pSignalLayout->addWidget(m_pSignalDisplay);
        m_pSignalLayout->addWidget(m_pFilteredSignalDisplay);
        //m_pSignalLayout->addWidget(groupBoxSignal);

    m_pFourierLayout = new QHBoxLayout();
        m_pFourierLayout->addWidget(m_pBufferedSignalDisplay);
        m_pFourierLayout->addWidget(m_pPowerSpectrumDisplay);

    m_pMainLayout = new QVBoxLayout();
        m_pMainLayout->addLayout(m_pSignalLayout);
        m_pMainLayout->addLayout(m_pFourierLayout);


    // attachs the layout to the main window
    setLayout(m_pMainLayout);

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

    if (nullptr != m_pFourierLayout)
        delete m_pFourierLayout;
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

