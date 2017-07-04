QT += qml quick 
TARGET = TsunamiMaster
TEMPLATE = app 
SOURCES += main.cpp
HEADERS += ../../include/Calclib/Common.h
RESOURCES += qml.qrc
CONFIG += console

include( ../../Common.pri )
include( ../../App.pri )
#LIBS += -lcalclib$${LIB_SUFFIX}

QML_IMPORT_PATH =

