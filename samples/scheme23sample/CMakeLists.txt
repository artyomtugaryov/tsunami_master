CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2)

PROJECT(scheme23sample)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

link_directories(${LIBRARY_OUTPUT_DIRECTORY})

file(GLOB scheme23sample_SRC	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB scheme23sample_HEADERS ${COMMON_INCLUDE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

include_directories(${COMMON_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${scheme23sample_SRC} ${scheme23sample_HEADERS})

target_link_libraries(${PROJECT_NAME} TMlib)