QT += core

include( $${_PRO_FILE_PWD_}/../../common.pri )
include( $${_PRO_FILE_PWD_}/../../lib.pri )

TARGET = TMlib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += TMLIB_LIBRARY

SOURCES += TMMapArea.cpp \
           TMMapAreaWorker.cpp \
           TMSchemeGroundswell.cpp \
           TMSchemeLandSearch.cpp \
           TMMapAreaWorkerGroundswell.cpp \

INCLUDEPATH += $${_PRO_FILE_PWD_}/../../include/TMlib/
HEADERS += $${_PRO_FILE_PWD_}/../../include/TMlib/TMMapArea.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMMapAreaWorker.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMException.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMSchemeGroundswell.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMSchemeLandSearch.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMMapAreaWorkerGroundswell.h \
