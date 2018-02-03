CONFIG +=c++11

PROJECT_ROOT_PATH = $${PWD}/

win32: OS_SUFFIX = win32
linux-g++: OS_SUFFIX = linux

CONFIG(debug, debug|release) {
    BUILD_FLAG = Debug
} else {
    BUILD_FLAG = Release
}
linux-g++ {
   !contains(QT_ARCH, x86_64){
       ARCH=x32
       message("Compiling for 32bit system")
    } else {
       ARCH=x64
       message("Compiling for 64bit system")
   }
}
win{
    !contains(QMAKE_TARGET.arch, x86_64) {
       ARCH=x32
       message("Compiling for 32bit system")
    } else {
       ARCH=x64
       message("Compiling for 64bit system")
    }
    win32-g++ {
        QMAKE_CXXFLAGS += -Werror
    }
    win32-msvc*{
        QMAKE_CXXFLAGS += /WX
    }
}
INC_PATH = $${PROJECT_ROOT_PATH}/include/
IMPORT_PATH = $${PROJECT_ROOT_PATH}/import/
BIN_PATH = $${PROJECT_ROOT_PATH}/bin/$${ARCH}/$${BUILD_FLAG}/
LIBS_PATH = $${BIN_PATH}/lib/
BUILD_PATH = $${PROJECT_ROOT_PATH}/build/$${BUILD_FLAG}/$${TARGET}/

RCC_DIR = $${BUILD_PATH}/rcc/
UI_DIR = $${BUILD_PATH}/ui/
MOC_DIR = $${BUILD_PATH}/moc/
OBJECTS_DIR = $${BUILD_PATH}/obj/
LIBS += -L$${LIBS_PATH}/
INCLUDEPATH += $${INC_PATH}/
INCLUDEPATH += $${IMPORT_PATH}/

linux-g++: QMAKE_CXXFLAGS += -std=c++11
