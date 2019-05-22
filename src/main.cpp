#include <QApplication>
#include <QObject>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QSignalMapper>

#include "SerialPortManager.h"
#include "SignalProcessing.h"
#include "TemporalSignalDisplay.h"
#include "SineGenerator.h"
#include "TemporalFilter.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //=======SERIAL PORT=========
    // creates a serial port manager object
    SerialPortManager spm(false);

    // sets serial port features
    spm.setBufferSize(100);
    spm.setBaudRate(9600);
    spm.setDataBits(8);
    spm.setParity(0);
    spm.setStopBits(1);
    spm.setFlowControl(0);
    spm.setBufferBeginKeyword("Sensor:");
    spm.setBufferEndKeyword("\n");
    spm.setValueSeparator('|');

    // finds the serial port
    spm.findSerialPort("Arduino");

    //=======SINE GENERATOR=========
    // creates a sine generator
    SineGenerator signalGenerator;

    // sets generator features
    signalGenerator.setNbSignals(5);
    signalGenerator.setFps(10.0);
    std::vector<float> vAmplitudes{ 10.0f, 20.0f, 30.0f, 40.0f, 50.0f };
    signalGenerator.setAmplitudes(vAmplitudes);
    std::vector<float> vFrequencies{ 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };
    signalGenerator.setFrequencies(vFrequencies);
    //std::vector<float> vPhases{ 0.0f, (float)M_PI / 4.0f, (float)M_PI / 2.0f, 3.0f * (float)M_PI / 4.0f, 0.0f };
    std::vector<float> vPhases{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    signalGenerator.setPhases(vPhases);

    //=======SERIALPORT OR SINE GENERATOR=========
    // either open the serial port or the signal generator
    if (false)
    {
        // opens the serial port
        spm.openSerialPort();

        // at this point, the spm object is sending data through its sigBroadcastSerialPortValues signal
    }
    else
    {
        signalGenerator.startWork();
    }

    //=======SIGNAL PROCESSING=========
    // creates a signal processing object
    SignalProcessing sp;

    // connects the signal from serial port manager (or sine generator) to a slot of the signal processing object
    QObject::connect(&spm, SIGNAL(sigBroadcastSerialPortValues(std::vector<float>)), &sp, SLOT(setInputData(std::vector<float>)));
    QObject::connect(&signalGenerator, SIGNAL(sigBroadcastSignalValues(std::vector<float>)), &sp, SLOT(setInputData(std::vector<float>)));

    //=======SIGNAL DISPLAY=========
    // creates a signal display object
    TemporalSignalDisplay disp;
        disp.setWidgetSize(QSize(640, 480));
        std::vector<std::string> vSignalLabels;
        vSignalLabels.push_back("1");vSignalLabels.push_back("2");vSignalLabels.push_back("3");vSignalLabels.push_back("4");vSignalLabels.push_back("5");
        disp.setSignalLabels(vSignalLabels);
        disp.setFps(10.f); // watch out fps must be set before setting XY range AND must be the same than the retrieved signals (from serial port or sine generator)
        disp.setXYRange(QSize(0, 20), QSize(250, 350)); // for arduino if nothing connected to analogic inputs (A0..A5)
        disp.setXYRange(QSize(0, 20), QSize(-60, 60)); // for the sine generator
        disp.setLegends("Time (s)", "Signal (V)");
        disp.setTicks(5, 5);
        disp.setDrawLine(true);

     // creates a signal display object for filtered signals
     TemporalSignalDisplay dispFilt;
        dispFilt.setWidgetSize(QSize(640, 480));
        dispFilt.setSignalLabels(vSignalLabels);
        dispFilt.setFps(10.f); // watch out fps must be set before setting XY range AND must be the same than the retrieved signals (from serial port or sine generator)
        dispFilt.setXYRange(QSize(0, 20), QSize(250, 350)); // for arduino if nothing connected to analogic inputs (A0..A5)
        dispFilt.setXYRange(QSize(0, 20), QSize(-60, 60)); // for the sine generator
        dispFilt.setLegends("Time (s)", "Signal (V)");
        dispFilt.setTicks(5, 5);
        dispFilt.setDrawLine(true);

    // connects the signal from serial port manager (or sine generator) to a slot of the temporal signal display object
    QObject::connect(&spm, SIGNAL(sigBroadcastSerialPortValues(std::vector<float>)), &disp, SLOT(setNewValues(std::vector<float>)));
    QObject::connect(&signalGenerator, SIGNAL(sigBroadcastSignalValues(std::vector<float>)), &disp, SLOT(setNewValues(std::vector<float>)));

    QObject::connect(&sp, SIGNAL(sigBroadcastFilteredValues(std::vector<float>)), &dispFilt, SLOT(setNewValues(std::vector<float>)));

    // creates an array of checkboxes to enabe/disable the display of specific signals
    QGroupBox *groupBoxSignal = new QGroupBox("Signal");
    QVBoxLayout *vboxSignal = new QVBoxLayout;
    std::vector<QCheckBox*> vSignalCheckBoxes;

    for (int l_cb = 0; l_cb < vSignalLabels.size(); l_cb++)
    {
        QCheckBox* l_ocb = new QCheckBox(QString::fromStdString(vSignalLabels[l_cb]));
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
    for (int l_cb = 0; l_cb < vSignalLabels.size(); l_cb++)
    {
        QObject::connect(vSignalCheckBoxes[l_cb], SIGNAL(stateChanged(int)), sigMapper, SLOT(map()));
        sigMapper->setMapping(vSignalCheckBoxes[l_cb], l_cb);
    }
    QObject::connect(sigMapper, SIGNAL(mapped(int)), &disp, SLOT(setSignalEnabled(int)));

     //=======MAIN WINDOW=========
    // creates the Main Window and a horizontal layout
    MainWindow* window = new MainWindow;
    QHBoxLayout* mainLayout = new QHBoxLayout;

    // resizes the main window
    window->resize(1800, 500);

    // attachs the signal display to the layout
    mainLayout->addWidget(&disp);
    mainLayout->addWidget(groupBoxSignal);
    mainLayout->addWidget(&dispFilt);

    // attachs the layout to the main window
    window->setLayout(mainLayout);

    // shows the main window
    window->show();

    return app.exec();
}
