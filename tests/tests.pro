QT += testlib

TARGET = TsunamiMasterTests
TEMPLATE = app 
SOURCES += \
            TMMapAreaTests.cpp

HEADERS += \
            ../include/TMlib/TMMapArea.h \
            TestCommon.h \
            TMMapAreaTests.h

INCLUDEPATH += $${_PRO_FILE_PWD_}/../include/TMlib/

include( ../common.pri )
include( ../app.pri )

LIBS += -lTMlib$${LIB_SUFFIX}

