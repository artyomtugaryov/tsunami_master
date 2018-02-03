QT += core

include( $${_PRO_FILE_PWD_}/../../common.pri )
include( $${_PRO_FILE_PWD_}/../../lib.pri )

TARGET = TMlib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += TMLIB_LIBRARY

SOURCES += TMMapArea.cpp \
           TMMapAreaWorker.cpp \
           TMCommon.cpp \
           TMScheme24.cpp \
           TMFocus.cpp \
           TMBlock.cpp \
           TMException.cpp \
           TMSignal.cpp

INCLUDEPATH += $${_PRO_FILE_PWD_}/../../include/TMlib/

HEADERS += $${_PRO_FILE_PWD_}/../../include/TMlib/TMMapArea.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMMapAreaWorker.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMException.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMCommon.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMConstants.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMScheme.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMScheme24.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMFocus.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMBlock.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMSignal.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMCommon.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMConstants.h
