QT += qml quick 

TARGET = TsunamiMaster
TEMPLATE = app

!include( $${_PRO_FILE_PWD_}/../../common.pri ): error(include file not found)
!include( $${_PRO_FILE_PWD_}/../../app.pri ): error(include file not found)

SOURCES += main.cpp

HEADERS += $${_PRO_FILE_PWD_}/../../include/HDlib/common.h
RESOURCES += qml.qrc
CONFIG += console


LIBS += -lHDlib$${LIB_SUFFIX}

QMAKE_CXXFLAGS += -Werror

