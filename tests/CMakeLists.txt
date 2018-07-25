cmake_minimum_required(VERSION 3.0)

project(TsunamiMasterTests)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

####################################
## All next project will use C++11
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
####################################

add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

link_directories(${LIBRARY_OUTPUT_DIRECTORY})

add_subdirectory(TMLibTests)