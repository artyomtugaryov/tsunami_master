QT += qml quick 

TARGET = TsunamiMaster
TEMPLATE = app

include( ../../common.pri )
include( ../../app.pri )

SOURCES += main.cpp

HEADERS +=  ../../include/HDlib/common.h
RESOURCES += qml.qrc
CONFIG += console

QMAKE_CXXFLAGS += -Werror
LIBS += -lcalclib$${LIB_SUFFIX}
