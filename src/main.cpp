#include <QApplication>

#include "ArduinoSimulator.h"
#include "ArduinoSimulatorGUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //=======ARDUINO SIMULATOR=========
    // creates the Arduino simulator
	ArduinoSimulator sim;

    //=======MainWindow=========
    // creates the Main Window
    ArduinoSimulatorGUI gui;
    // shows the main window
    gui.show();

    //=======Qt CONNECTIONS=========
    QObject::connect(&gui, SIGNAL(sendDataFilename(QString)), &sim,    SLOT(setDataFile(QString)));


    return app.exec();
}

