QT = core bluetooth widgets
requires(qtConfig(listwidget))

SOURCES = \
	main.cpp \
	ArduinoSimulator.cpp \
	BtServer.cpp \
	BtClient.cpp
    

HEADERS = \
	ArduinoSimulator.h \
	BtServer.h \
	BtClient.h
	
	
    
