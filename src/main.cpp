#include <QApplication>

#include "SerialPortManager.h"
#include "SignalProcessing.h"
#include "SineGenerator.h"
#include "MainWindow.h"

#define ARDUINO false

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
    signalGenerator.setFps(100.0);
    std::vector<float> vAmplitudes{ 50.0f, 50.0f, 50.0f, 50.0f, 50.0f };
    signalGenerator.setAmplitudes(vAmplitudes);
    std::vector<float> vFrequencies{ 1.0f, 2.0f, 3.0f, 5.0f, 10.0f };
    signalGenerator.setFrequencies(vFrequencies);
    std::vector<float> vPhases{ 0.0f, (float)M_PI / 4.0f, (float)M_PI / 2.0f, 3.0f * (float)M_PI / 4.0f, 0.0f };
    signalGenerator.setPhases(vPhases);

    //=======SERIALPORT OR SINE GENERATOR=========
    // either open the serial port or the signal generator
    if (ARDUINO)
    {
        // opens the serial port
        spm.openSerialPort();

        // at this point, the spm object is sending data through its sigBroadcastSerialPortValues signal
    }
    else
    {
        // start the worker
        signalGenerator.startWork();

        // at this point, the signalGenerator object is sending data through its sigBroadcastSerialPortValues signal
    }

    //=======SIGNAL PROCESSING=========
    // creates a signal processing object
    SignalProcessing sp;
    sp.setNbSignals(5);

    //=======MAIN WINDOW=========
    // creates the Main Window
    MainWindow window;
    // shows the main window
    window.show();

    //=======Qt CONNECTIONS=========
    if (ARDUINO)
    {
        QObject::connect(&spm, SIGNAL(sigBroadcastSignalValues(std::vector<float>)), &window, SLOT(setSignalValues(std::vector<float>)));
        QObject::connect(&spm, SIGNAL(sigBroadcastSerialPortValues(std::vector<float>)), &sp, SLOT(setInputData(std::vector<float>)));
    }
    else
    {
        QObject::connect(&signalGenerator, SIGNAL(sigBroadcastSignalValues(std::vector<float>)), &window, SLOT(setSignalValues(std::vector<float>)));
        QObject::connect(&signalGenerator, SIGNAL(sigBroadcastSignalValues(std::vector<float>)), &sp, SLOT(setInputData(std::vector<float>)));
    }

    QObject::connect(&sp, SIGNAL(sigBroadcastFilteredValues(std::vector<float>)), &window, SLOT(setFilteredSignalValues(std::vector<float>)));

    return app.exec();
}
