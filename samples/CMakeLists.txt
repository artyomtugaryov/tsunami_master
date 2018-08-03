CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2)

PROJECT(samples)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

link_directories(${LIBRARY_OUTPUT_DIRECTORY})

add_subdirectory(scheme23sample)
