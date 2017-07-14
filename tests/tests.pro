QT += testlib

TARGET = TsunamiMasterTests
TEMPLATE = app 
SOURCES += common_test.cpp
HEADERS += common_test.h \
           ../include/TMlib/TMMapArea.h

include( ../common.pri )
include( ../app.pri )

LIBS += -lTMlib$${LIB_SUFFIX}
#LIBS += -lgdi32

