QT += qml quick

TARGET = TsunamiMaster
TEMPLATE = app

!include( $${_PRO_FILE_PWD_}/../../common.pri ): error(include file not found)
!include( $${_PRO_FILE_PWD_}/../../app.pri ): error(include file not found)

SOURCES += main.cpp \
           ApplicationGUI.cpp

HEADERS += ApplicationGUI.h

HEADERS += $${_PRO_FILE_PWD_}/../../include/TMlib
RESOURCES += qml.qrc
CONFIG += console

LIBS += -lTMlib$${LIB_SUFFIX}

QMAKE_CXXFLAGS += -Werror
