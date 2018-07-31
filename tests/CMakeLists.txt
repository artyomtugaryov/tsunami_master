CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(TsunamiMasterTests)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

link_directories(${LIBRARY_OUTPUT_DIRECTORY})

add_subdirectory(TMLibTests)
