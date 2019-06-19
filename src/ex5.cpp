#include <QApplication>

#include "SineGenerator.h"
#include "MainWindowEx5.h"
#include "SignalProcessing.h"

#define NB_SIGNALS 5
#define FPS 100.0

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	//=======SINE GENERATOR=========
	// creates a sine generator
	SineGenerator signalGenerator;

	// sets generator features
	signalGenerator.setNbSignals(NB_SIGNALS);
	signalGenerator.setFps(FPS);
	std::vector<float> vAmplitudes{ 50.0f, 50.0f, 50.0f, 50.0f, 50.0f };
	signalGenerator.setAmplitudes(vAmplitudes);
	std::vector<float> vFrequencies{ 1.0f, 2.0f, 3.0f, 5.0f, 10.0f };
	signalGenerator.setFrequencies(vFrequencies);
	std::vector<float> vPhases{ 0.0f, (float)M_PI / 4.0f, (float)M_PI / 2.0f, 3.0f * (float)M_PI / 4.0f, 0.0f };
	signalGenerator.setPhases(vPhases);
	
	// starts the worker
	signalGenerator.startWork();

	// at this point, the signalGenerator object is sending data through its sigBroadcastSignalValues signal

	//=======SIGNAL PROCESSING=========
	// creates a signal processing object
	SignalProcessing sp;
	sp.setNbSignals(NB_SIGNALS);
	
	//=======MainWindow=========
	// creates the Main Window
	MainWindowEx5 window;
	// shows the main window
	window.show();
	
	//=======Qt CONNECTIONS=========
	QObject::connect(&signalGenerator, SIGNAL(sigBroadcastSignalValues(float, std::vector<float>)), &window,    SLOT(setSignalValues(float, std::vector<float>)));
	QObject::connect(&signalGenerator, SIGNAL(sigBroadcastSignalValues(float, std::vector<float>)), &sp,        SLOT(setSignalValues(float, std::vector<float>)));
	
	QObject::connect(&sp,       SIGNAL(sigBroadcastFilteredSignalValues(std::vector<float>)),               &window,    SLOT(setFilteredSignalValues(std::vector<float>)));
   


	return app.exec();
}
