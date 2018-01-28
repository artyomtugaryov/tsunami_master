QT += core quick

include( $${_PRO_FILE_PWD_}/../../common.pri )
include( $${_PRO_FILE_PWD_}/../../lib.pri )

TARGET = TsunamiManagerlib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += TSUNAMIMANAGER_LIBRARY

SOURCES+= TsunamiManager.cpp \
          TsunamiWorker.cpp \
          TsunamiPlotProvider.cpp \
          TsunamiData.cpp

HEADERS += $${_PRO_FILE_PWD_}/../../include/TsunamiManager/TsunamiManager.h \
           $${_PRO_FILE_PWD_}/../../include/TsunamiManager/TsunamiData.h \
           $${_PRO_FILE_PWD_}/../../include/TsunamiManager/TsunamiWorker.h \
           $${_PRO_FILE_PWD_}/../../include/TsunamiManager/TsunamiPlotProvider.h \
           $${_PRO_FILE_PWD_}/../../include/PlotLib \

INCLUDEPATH += $${_PRO_FILE_PWD_}/../../include/TMlib/
INCLUDEPATH += $${_PRO_FILE_PWD_}/../../include/PlotLib/

LIBS += -lTMlib$${LIB_SUFFIX}
LIBS += -lPlotLib$${LIB_SUFFIX}
