QT += qml quick 
TARGET = TsunamiMasterTests
TEMPLATE = app 
SOURCES += common_test.cpp
HEADERS += common_test.h \
            ../include/calclib/common.h
include( ../common.pri )
include( ../app.pri )
LIBS += -lcalclib$${LIB_SUFFIX}
