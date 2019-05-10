QT +=  widgets serialport

INCLUDEPATH += include

HEADERS = 	include/SerialPortManager.h \
                include/SignalProcessing.h \
                include/TemporalSignalDisplay.h \
                include/MainWindow.h

SOURCES = 	src/SerialPortManager.cpp \
                src/SignalProcessing.cpp \
                src/TemporalSignalDisplay.cpp \
                src/MainWindow.cpp \
                src/main.cpp
   
                
