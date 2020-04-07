QT +=  widgets serialport

INCLUDEPATH += include

HEADERS = 	include/SerialPortManager.h \
			include/MainWindow.h \
			include/SignalDisplay.h \
			include/TemporalSignalDisplay.h \
			include/BufferedSignalDisplay.h \
                        include/MainWindowEx7.h \
		
SOURCES = 	src/SerialPortManager.cpp \
			src/MainWindow.cpp \
			src/SignalDisplay.cpp \
			src/TemporalSignalDisplay.cpp \
			src/BufferedSignalDisplay.cpp \
                        src/MainWindowEx7.cpp \
		        src/ex7.cpp
   
                
