include(gtest_dependency.pri)

TEMPLATE = subdirs
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

SUBDIRS += \
        TMLibTests \
