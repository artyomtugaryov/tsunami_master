QT += testlib

TARGET = TsunamiMasterTests
TEMPLATE = app 
SOURCES += \
            TMMapAreaTests.cpp \
    main.cpp \
    TestCommon.cpp \
    TMMapAreaTests.cpp \
    TMScheme24Tests.cpp
            TMScheme24Tests.cpp
            main.cpp

HEADERS += \
            TestCommon.h \
            TMMapAreaTests.h \
    TestCommon.h \
    TMMapAreaTests.h \
    TMScheme24Tests.h
            TMScheme24Tests.h

INCLUDEPATH += $${_PRO_FILE_PWD_}/../include/TMlib/

include( ../common.pri )
include( ../app.pri )

LIBS += -lTMlib$${LIB_SUFFIX}

SUBDIRS += \
    tests.pro

DISTFILES +=

