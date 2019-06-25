#include "MainWindowEx4.h"
#include <QDebug>

#define FPS 100.0

MainWindowEx4::MainWindowEx4()
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
   
    // resizes the main window
    resize(800, 500);

    // designs the interface
    m_pSignalLayout = new QHBoxLayout();
        m_pSignalLayout->addWidget(m_pSignalDisplay);
        m_pSignalLayout->addWidget(groupBoxSignal);

    m_pMainLayout = new QHBoxLayout();
        m_pMainLayout->addLayout(m_pSignalLayout);
        

    // attachs the layout to the main window
    setLayout(m_pMainLayout);

}

MainWindowEx4::~MainWindowEx4()
{
    
}

