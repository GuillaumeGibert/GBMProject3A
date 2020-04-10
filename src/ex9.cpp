#include <QtWidgets/qapplication.h>

#include "ArduinoSimClient.h"
#include "MainWindowEx9.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    //=======ARDUINO SIM CLIENT=========
    ArduinoSimClient simClient;
    simClient.setBufferBeginKeyword("Sensor:");
    simClient.setBufferEndKeyword("\n");
    simClient.setValueSeparator('|');

    //=======MainWindow=========
    // creates the Main Window
    MainWindowEx9 window;
    // shows the main window
    #ifdef Q_OS_ANDROID
        window.showMaximized();
    #else
        window.show();
    #endif

    //=======Qt CONNECTIONS=========
    QObject::connect(&window, SIGNAL(searchBtServer()), &simClient,    SLOT(searchBtServer()));
    QObject::connect(&simClient, SIGNAL(sigBroadcastSignalValues(float, std::vector<float>)), &window,    SLOT(setSignalValues(float, std::vector<float>)));
    QObject::connect(&window, &MainWindowEx9::quit, &app,  &QApplication::quit);

    app.exec();

    return 0;
}
