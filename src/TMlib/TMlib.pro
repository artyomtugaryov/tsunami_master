QT += core

include( $${_PRO_FILE_PWD_}/../../common.pri )
include( $${_PRO_FILE_PWD_}/../../lib.pri )

TARGET = TMlib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += TMLIB_LIBRARY

SOURCES += TMBlock.cpp \
           TMBrickPoint.cpp \
           TMBrickUp.cpp \
           TMCommon.cpp \
           TMException.cpp \
           TMFocus.cpp \
           TMHelpers.cpp \
           TMKolchScheme.cpp \
           TMMapArea.cpp \
           TMMapAreaWorker.cpp \
           TMMareograph.cpp \
           TMScheme.cpp \
           TMScheme23.cpp \

INCLUDEPATH += $${_PRO_FILE_PWD_}/../../include/TMlib/

HEADERS += $${_PRO_FILE_PWD_}/../../include/TMlib/TMBlock.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMBrickPoint.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMBrickUp.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMCommon.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMConstants.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMException.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMFocus.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMHelpers.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMKolchScheme.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMMapArea.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMMapAreaWorker.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMMareograph.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/scheme.h \
           $${_PRO_FILE_PWD_}/../../include/TMlib/TMScheme23.h \
#TODO: For test. Remove after all work with calculation part.
           $${_PRO_FILE_PWD_}/../../include/PlotLib \

INCLUDEPATH += $${_PRO_FILE_PWD_}/../../include/PlotLib/
LIBS += -lPlotLib$${LIB_SUFFIX}
#TODO END

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp
