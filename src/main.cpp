#include <QApplication>
#include <QObject>

#include "SerialPortManager.h"
#include "SignalProcessing.h"
#include "TemporalSignalDisplay.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    // creates a serial port manager object with verbose mode
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

    // opens the serial port
    spm.openSerialPort();

    // at this point, the spm object is sending data through its sigBroadcastSerialPortValues signal


    // creates a signal processing object
    SignalProcessing sp;

    // connects the signal from serial port manager to a slot of the signal processing object
    QObject::connect(&spm, SIGNAL(sigBroadcastSerialPortValues(std::vector<float>)), &sp, SLOT(setInputData(std::vector<float>)));

    // creates a signal display object
    TemporalSignalDisplay disp;
        disp.setWidgetSize(QSize(640, 480));
        std::vector<std::string> vSignalLabels;
        vSignalLabels.push_back("1");vSignalLabels.push_back("2");vSignalLabels.push_back("3");vSignalLabels.push_back("4");vSignalLabels.push_back("5");
        disp.setSignalLabels(vSignalLabels);
        disp.setXYRange(QSize(0, 20), QSize(-10, 10));
        disp.setLegends("Time (s)", "Signal (V)");
        disp.setFps(10.f);
        disp.setTicks(5, 5);
        disp.setDrawLine(true);

    // connects the signal from serial port manager to a slot of the signal processing object
    QObject::connect(&spm, SIGNAL(sigBroadcastSerialPortValues(std::vector<float>)), &disp, SLOT(setNewValues(std::vector<float>)));

    // shows the widget
    disp.show();

    return app.exec();
	

}
