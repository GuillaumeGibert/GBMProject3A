QT +=  widgets

INCLUDEPATH += include

HEADERS = 	include/SignalProcessing.h \
			include/TemporalFilter.h \
                        include/SineGenerator.h \
			include/MainWindow.h \
			include/SignalDisplay.h \
			include/TemporalSignalDisplay.h \
			include/BufferedSignalDisplay.h \
			include/MainWindowEx5.h \
		

SOURCES = 	src/SignalProcessing.cpp \
			src/TemporalFilter.cpp \
			src/SineGenerator.cpp \
			src/MainWindow.cpp \
			src/SignalDisplay.cpp \
			src/TemporalSignalDisplay.cpp \
			src/BufferedSignalDisplay.cpp \
                        src/MainWindowEx5.cpp \
			src/ex5.cpp
   
                
