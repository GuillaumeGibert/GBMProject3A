#include <QCoreApplication>
#include <QObject>

#include "SerialPortManager.h"
#include "SignalProcessing.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

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

    return a.exec();
	

}
