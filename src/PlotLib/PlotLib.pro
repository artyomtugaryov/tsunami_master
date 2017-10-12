QT += core

include( $${_PRO_FILE_PWD_}/../../common.pri )
include( $${_PRO_FILE_PWD_}/../../lib.pri )

CONFIG += c++11

TARGET = PlotLib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += PLOTLIB_LIBRARY

SOURCES += Plot2d.cpp \
          ColorMap.cpp

HEADERS += $${_PRO_FILE_PWD_}/../../include/PlotLib/Plot2D.h \
           $${_PRO_FILE_PWD_}/../../include/PlotLib/ColorMap.h

