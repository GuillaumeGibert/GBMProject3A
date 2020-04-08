QT = core bluetooth widgets
requires(qtConfig(listwidget))

INCLUDEPATH += include

SOURCES = \
        src/main.cpp \
        src/ArduinoSimulator.cpp \
        src/ArduinoSimulatorGUI.cpp \
        src/BtServer.cpp \
        src/BtClient.cpp
    

HEADERS = \
        include/ArduinoSimulator.h \
        include/ArduinoSimulatorGUI.h \
        include/BtServer.h \
        include/BtClient.h
	
	
    
