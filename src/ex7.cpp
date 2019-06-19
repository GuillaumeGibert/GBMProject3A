#include <QApplication>

#include "SerialPortManager.h"
#include "MainWindowEx7.h"



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

	// opens the serial port
	spm.openSerialPort();

	// at this point, the spm object is sending data through its sigBroadcastSignalValues signal
	
		
	//=======MainWindow=========
	// creates the Main Window
	MainWindowEx7 window;
	// shows the main window
	window.show();
	
	//=======Qt CONNECTIONS=========
    QObject::connect(&window, SIGNAL(sigSendButtonPressed(const QByteArray)), &spm,    SLOT(writeData(const QByteArray)));
	
	
	return app.exec();
}
