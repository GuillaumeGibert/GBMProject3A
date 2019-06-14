QT +=  widgets serialport

INCLUDEPATH += include

HEADERS = 	include/SerialPortManager.h \
                include/SignalProcessing.h \
                include/SignalDisplay.h \
                include/TemporalSignalDisplay.h \
		include/BufferedSignalDisplay.h \
                include/SineGenerator.h \
                include/TemporalFilter.h \
                include/MainWindow.h \
		include/Buffering.h \
		include/FFT.h

SOURCES = 	src/SerialPortManager.cpp \
                src/SignalProcessing.cpp \
                src/SignalDisplay.cpp \
                src/TemporalSignalDisplay.cpp \
		src/BufferedSignalDisplay.cpp \
                src/MainWindow.cpp \
                src/SineGenerator.cpp \
                src/TemporalFilter.cpp \
		src/Buffering.cpp \
		src/FFT.cpp \
                src/main.cpp
   
                
