cmake_minimum_required(VERSION 3.0.2)

project(TsunamiManager)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH $ENV{QT_ROOT})

find_package(Qt5Core)

file(GLOB TsunamiManager_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB TsunamiManager_HEADERS ${COMMON_INCLUDE_DIR}/TsunamiManager/*.h)

include_directories(${COMMON_INCLUDE_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS})

set(MOCS ${COMMON_INCLUDE_DIR}/TsunamiManager/*.h)

add_library(${PROJECT_NAME} SHARED  ${TsunamiManager_SRC}
                                    ${TsunamiManager_HEADERS})

add_dependencies(${PROJECT_NAME} PlotLib)

target_link_libraries(${PROJECT_NAME} Qt5::Core TMlib PlotLib)

