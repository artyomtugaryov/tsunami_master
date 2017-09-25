cmake_minimum_required(VERSION 3.0.2)

project(TsunamiManager)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

file(GLOB TsunamiManager_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB TsunamiManager_HEADERS ${COMMON_INCLUDE_DIR}/TsunamiManager/*.h)

include_directories(${COMMON_INCLUDE_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS})

set(MOCS ${COMMON_INCLUDE_DIR}/TsunamiManager/*.h)

add_library(${PROJECT_NAME} SHARED  ${TsunamiManager_SRC}
                                    ${TsunamiManager_HEADERS})

target_link_libraries(${PROJECT_NAME} TMlib)

qt5_use_modules(${PROJECT_NAME} Core Widgets)
