cmake_minimum_required(VERSION 2.8.13)

project("TMlib")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH $ENV{QT_ROOT})

find_package(Qt5 COMPONENTS Core Gui REQUIRED)

file(GLOB TMLIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB TMLIB_HEADERS ${COMMON_INCLUDE_DIR}/TMlib/*.h)

include_directories(${COMMON_INCLUDE_DIR})
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_library(${PROJECT_NAME} SHARED ${TMLIB_SRC} ${TMLIB_HEADERS} helpers.cpp ../../include/TMlib/helpers.h)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui PlotLib)