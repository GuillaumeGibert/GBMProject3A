#include <QApplication>

#include "SineGenerator.h"
#include "Spy.h"

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


	//=======SPY=========
	// creates a spy object
	Spy spy;

	//=======Qt CONNECTIONS=========
	QObject::connect(&signalGenerator, SIGNAL(sigBroadcastSignalValues(float, std::vector<float>)), &spy,    SLOT(setSignalValues(float, std::vector<float>)));



	return app.exec();
}
