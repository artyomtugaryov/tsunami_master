cmake_minimum_required(VERSION 3.2)

project(TMLibTests)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

####################################
## All next project will use C++11
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
####################################

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

link_directories(${LIBRARY_OUTPUT_DIRECTORY})

file(GLOB TEST_SRC	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB TEST_HEADERS ${COMMON_INCLUDE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


include_directories(${COMMON_INCLUDE_DIR})

add_executable(${PROJECT_NAME}  ${TEST_SRC})

target_link_libraries(${PROJECT_NAME} gtest gtest_main TMlib)
