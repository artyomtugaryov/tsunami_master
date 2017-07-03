include( ../../common.pri )
include( ../../lib.pri )
QT += core gui
TARGET = calclib$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += CALCLIB_LIBRARY 
SOURCES += ./*.cpp
HEADERS += ../../include/calclib/*.hpp
win32 {
     QMAKE_TARGET_PRODUCT = calclib
     QMAKE_TARGET_DESCRIPTION = Calculation library
}
