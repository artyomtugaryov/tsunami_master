QT += core

include( $${_PRO_FILE_PWD_}/../../common.pri )
include( $${_PRO_FILE_PWD_}/../../lib.pri )

TARGET = HDlib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += HDLIB_LIBRARY

SOURCES += common.cpp
HEADERS += $${_PRO_FILE_PWD_}/../../include/HDlib/common.h
