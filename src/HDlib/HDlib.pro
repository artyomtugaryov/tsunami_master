QT += core
TARGET = calclib$${LIB_SUFFIX}
QMAKE_CXXFLAGS += -Werror
include( ../../common.pri )
include( ../../lib.pri )
TEMPLATE = lib
DEFINES += CALCLIB_LIBRARY
SOURCES += common.cpp
HEADERS += ../../include/HDlib/common.h
win32 {
     QMAKE_TARGET_PRODUCT = calclib
     QMAKE_TARGET_DESCRIPTION = calculation library
}
