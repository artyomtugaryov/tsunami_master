QT += testlib

TARGET = TsunamiMasterTests
TEMPLATE = app 
SOURCES += common_test.cpp \
            testsmaparea.cpp
HEADERS += common_test.h \
           testsmaparea.h\
           ../include/HDlib/common.h \
           ../include/HDlib/MapArea.h

include( ../common.pri )
include( ../app.pri )

LIBS += -lHDlib$${LIB_SUFFIX}
#LIBS += -lgdi32

