QT += qml quick 
TARGET = TsunamiMasterTests
TEMPLATE = app 
SOURCES += common_test.cpp
HEADERS += common_test.h \
            ../include/HDlib/common.h
include( ../common.pri )
include( ../app.pri )

LIBS += -lHDlib$${LIB_SUFFIX}

