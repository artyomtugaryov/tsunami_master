include( ../../common.pri )
include( ../../lib.pri )
QT += core
TARGET = calclib$${LIB_SUFFIX}
TEMPLATE = lib
DEFINES += CALCLIB_LIBRARY 
SOURCES += common.cpp \
HEADERS += ../../include/calclib/common.h \
win32 {
     QMAKE_TARGET_PRODUCT = calclib
     QMAKE_TARGET_DESCRIPTION = Calculation library
}
