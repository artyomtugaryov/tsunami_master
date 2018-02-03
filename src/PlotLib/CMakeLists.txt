cmake_minimum_required(VERSION 3.0.2)

project(PlotLib)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH $ENV{QT_ROOT})

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

file(GLOB PlotLib_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB PlotLib_HEADERS ${COMMON_INCLUDE_DIR}/PlotLib/*.h)

set(MOCS ${COMMON_INCLUDE_DIR}/PlotLib/*.h)

include_directories(${COMMON_INCLUDE_DIR}
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${PlotLib_SRC} ${PlotLib_HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)