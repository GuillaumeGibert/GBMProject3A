TEMPLATE = app
TARGET = ArduinoSimClient

QT +=  core bluetooth widgets
requires(qtConfig(listwidget))
android: QT += androidextras

INCLUDEPATH += include

HEADERS = 	include/RemoteSelector.h \
			include/BtClient.h \
			include/ArduinoSimClient.h \
                
SOURCES = 	src/RemoteSelector.cpp \
			src/BtClient.cpp \
			src/ArduinoSimClient.cpp \
			src/ex9.cpp       

FORMS = \
    chat.ui \
    remoteselector.ui