QT += qml quick

TARGET = TsunamiMaster
TEMPLATE = app

!include( $${_PRO_FILE_PWD_}/../../common.pri ): error(include file not found)
!include( $${_PRO_FILE_PWD_}/../../app.pri ): error(include file not found)

SOURCES += main.cpp \
           ApplicationGUI.cpp \
           SourceGUI.cpp

HEADERS += ApplicationGUI.h \
           SourceGUI.h

HEADERS += $${_PRO_FILE_PWD_}/../../include/TMlib \
           $${_PRO_FILE_PWD_}/../../include/TsunamiManager \

RESOURCES += qml.qrc

CONFIG += console

LIBS += -lTMlib$${LIB_SUFFIX}
LIBS += -lTsunamiManagerlib$${LIB_SUFFIX}
INCLUDEPATH += $${_PRO_FILE_PWD_}/../../include/TMlib/
QMAKE_CXXFLAGS += -Werror
