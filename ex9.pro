TEMPLATE = app
TARGET = ArduinoSimClient

QT +=  core bluetooth widgets
requires(qtConfig(listwidget))
android: QT += androidextras

INCLUDEPATH += include

HEADERS = 	include/RemoteSelector.h \
                include/BtClient.h \
                include/ArduinoSimClient.h \
                include/MainWindow.h \
                include/SignalDisplay.h \
                include/TemporalSignalDisplay.h \
                include/BufferedSignalDisplay.h \
                include/MainWindowEx9.h \

                
SOURCES = 	src/RemoteSelector.cpp \
                src/BtClient.cpp \
                src/ArduinoSimClient.cpp \
                src/MainWindow.cpp \
                src/SignalDisplay.cpp \
                src/TemporalSignalDisplay.cpp \
                src/BufferedSignalDisplay.cpp \
                src/MainWindowEx9.cpp \
                src/ex9.cpp

FORMS =         ui/remoteselector.ui
