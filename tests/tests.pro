QT += qml quick 
TARGET = TsunamiMasterTests
TEMPLATE = app 
SOURCES += ./*cpp
HEADERS += ./*.hpp \
            ../include/calclib/*.hpp
include( ../common.pri )
include( ../app.pri )
#LIBS += -lcalclib$${LIB_SUFFIX}
