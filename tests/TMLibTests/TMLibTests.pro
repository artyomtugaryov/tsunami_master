include(../gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

SOURCES += \
    TMBOperatorsTests.cpp \
    TMBrickPointTests.cpp \
    TMScheme23Tests.cpp \

INCLUDEPATH += $${_PRO_FILE_PWD_}/../../include/TMlib/
