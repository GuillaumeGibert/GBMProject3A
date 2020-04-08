#include <QApplication>

#include "SerialPortManager.h"
#include "Spy.h"

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
    //spm.setFirstPortFound(false);

	// finds the serial port
	spm.findSerialPort("Bluetooth");

	// opens the serial port
	spm.openSerialPort();

	// at this point, the spm object is sending data through its sigBroadcastSignalValues signal
	
	//=======SPY=========
	// creates a spy object
	Spy spy;
	
	//=======Qt CONNECTIONS=========
	QObject::connect(&spm, SIGNAL(sigBroadcastSignalValues(float, std::vector<float>)), &spy,    SLOT(setSignalValues(float, std::vector<float>)));
       
	

	return app.exec();
}
