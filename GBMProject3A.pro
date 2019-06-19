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
		include/MainWindowEx4.h \
                include/MainWindowEx5.h \
                include/MainWindowEx6.h \
                include/MainWindowEx7.h \
		include/Buffering.h \
                include/FFT.h \
                include/Spy.h

SOURCES = 	src/SerialPortManager.cpp \
                src/SignalProcessing.cpp \
                src/SignalDisplay.cpp \
                src/TemporalSignalDisplay.cpp \
		src/BufferedSignalDisplay.cpp \
                src/MainWindow.cpp \
		src/MainWindowEx4.cpp \
                src/MainWindowEx5.cpp \
                src/MainWindowEx6.cpp \
                src/MainWindowEx7.cpp \
                src/SineGenerator.cpp \
                src/TemporalFilter.cpp \
		src/Buffering.cpp \
		src/FFT.cpp \
                src/Spy.cpp \
                src/ex5.cpp
   
                
