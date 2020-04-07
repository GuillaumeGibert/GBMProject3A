QT +=  widgets sql

INCLUDEPATH += include

HEADERS = 	include/MainWindow.h \
			include/SignalDisplay.h \
			include/TemporalSignalDisplay.h \
			include/BufferedSignalDisplay.h \
			include/MainWindowEx8.h \
			include/DatabaseManager.h

SOURCES = 	src/MainWindow.cpp \
			src/SignalDisplay.cpp \
			src/TemporalSignalDisplay.cpp \
			src/BufferedSignalDisplay.cpp \
			src/MainWindowEx8.cpp \
			src/DatabaseManager.cpp \
			src/ex8.cpp
