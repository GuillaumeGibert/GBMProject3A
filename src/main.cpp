#include "ArduinoSimulator.h"

#include <QtWidgets/qapplication.h>

int main(int argc, char *argv[])
{
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);

	ArduinoSimulator sim;

	app.exec();

	return 0;
}

