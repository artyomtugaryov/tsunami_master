include( $${_PRO_FILE_PWD_}/../gtest_dependency.pri)
include( $${_PRO_FILE_PWD_}/../../common.pri )
include( $${_PRO_FILE_PWD_}/../../lib.pri )
TEMPLATE = app

SOURCES += \
    TMBOperatorsTests.cpp \
    TMBrickPointTests.cpp \
    TMScheme23Tests.cpp \
    ../main.cpp \

INCLUDEPATH += $${_PRO_FILE_PWD_}/../../include/

LIBS += -lTMlib$${LIB_SUFFIX}
