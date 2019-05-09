QT +=  widgets serialport

INCLUDEPATH += include

HEADERS = 	include/SerialPortManager.h \
			include/SignalProcessing.h \
			include/TemporalSignalDisplay.h

SOURCES = 	src/SerialPortManager.cpp \
			src/SignalProcessing.cpp \
			src/TemporalSignalDisplay.cpp \
			src/main.cpp 
   
                
