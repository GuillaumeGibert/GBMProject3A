#include <QApplication>

#include "ArduinoSimClient.h"
#include "MainWindowEx9.h"
#include "Buffering.h"
#include "FFT.h"

#define NB_SIGNALS 5
#define FPS 10.0

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //=======ARDUINO SIM CLIENT=========
    ArduinoSimClient simClient;
    simClient.setBufferBeginKeyword("Sensor:");
    simClient.setBufferEndKeyword("\n");
    simClient.setValueSeparator('|');

    //=======BUFFERING=========
    // creates a buffering object
    Buffering buffer;
    buffer.setFps(FPS);
    buffer.setNbSignals(NB_SIGNALS);
    buffer.setDuration(2.0);
    buffer.setShift(1.0);

    //=======FFT=========
    // creates a FFT object
    FFT fft;
    fft.setFps(FPS);
    fft.setNbSignals(NB_SIGNALS);

    //=======MainWindow=========
    // creates the Main Window
    MainWindowEx9 window;
    // shows the main window
    window.show();

    //=======Qt CONNECTIONS=========
    QObject::connect(&window, SIGNAL(searchBtServer()), &simClient,    SLOT(searchBtServer()));

    QObject::connect(&simClient, SIGNAL(sigBroadcastSignalValues(float, std::vector<float>)), &window,    SLOT(setSignalValues(float, std::vector<float>)));
    QObject::connect(&simClient, SIGNAL(sigBroadcastSignalValues(float, std::vector<float>)), &buffer,        SLOT(setSignalValues(float, std::vector<float>)));
    QObject::connect(&buffer,   SIGNAL(sigBroadcastBufferedSignalValues(std::vector<std::deque<float>>)),   &fft,       SLOT(setBufferedSignalValues(std::vector<std::deque<float>>)));
    QObject::connect(&fft,      SIGNAL(sigBroadcastPowerSpectrumValues(std::vector<std::deque<float>>)),    &window,    SLOT(setPowerSpectrumValues(std::vector<std::deque<float>>)));

    return app.exec();
}
