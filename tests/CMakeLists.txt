cmake_minimum_required(VERSION 2.8)

project(TsunamiMasterTests)

####################################
## All next project will use C++11
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
####################################

set(DATA_PATH ${TEMP}/validation_set/daily)
message(STATUS "DATA_PATH ............................. " ${DATA_PATH})

enable_testing()
link_directories(${LIBRARY_OUTPUT_DIRECTORY})

file(GLOB TEST_SRC 
	{CMAKE_CURRENT_DIRECTORY}/*.cpp
)
