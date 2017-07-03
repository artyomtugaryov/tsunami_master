QT += qml quick 
TARGET = TsunamiMaster
TEMPLATE = app 
SOURCES += main.cpp
RESOURCES += qml.qrc

include( ../../common.pri ) 
include( ../../app.pri ) 
#LIBS += -lcalclib$${LIB_SUFFIX}

QML_IMPORT_PATH =

include(deployment.pri)
