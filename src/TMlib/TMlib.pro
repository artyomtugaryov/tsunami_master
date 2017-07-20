QT += core
s
include( $${_PRO_FILE_PWD_}/../../common.pri )
include( $${_PRO_FILE_PWD_}/../../lib.pri )

TARGET = TMlib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += TMLIB_LIBRARY

SOURCES += TMMapArea.cpp \
           TMMapAreaWorker.cpp

INCLUDEPATH += $${_PRO_FILE_PWD_}/../../include/TMlib/
HEADERS += $${_PRO_FILE_PWD_}/../../include/TMlib/TMMapArea.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMMapAreaWorker.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMException.h
