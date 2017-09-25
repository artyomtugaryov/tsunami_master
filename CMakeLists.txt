cmake_minimum_required(VERSION 3.0.2)

project(TsunamiManager)

set(DEV_BUILD TRUE)

if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set (ARCH_FOLDER x64)
else()
    set (ARCH_FOLDER x32)
endif()

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include (debug)

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    debug_message(STATUS "CMAKE_BUILD_TYPE not defined, 'Release' will be used")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if (UNIX)
    SET(LIB_DL dl)
endif()

set (TM_MAIN_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (OUTPUT_ROOT ${TM_MAIN_SOURCE_DIR})
set (COMMON_INCLUDE_DIR ${TM_MAIN_SOURCE_DIR}/include)
set (BIN_DIR bin/${ARCH_FOLDER})


set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_ROOT}/${BIN_DIR}/${CMAKE_BUILD_TYPE}/lib)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_ROOT}/${BIN_DIR}/${CMAKE_BUILD_TYPE}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_ROOT}/${BIN_DIR}/${CMAKE_BUILD_TYPE})
set (LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_ROOT}/${BIN_DIR}/${CMAKE_BUILD_TYPE}/lib)
set (LIBRARY_OUTPUT_PATH ${LIBRARY_OUTPUT_DIRECTORY})

#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

message("=====================> ${CMAKE_BUILD_TYPE} <=====================")

message (STATUS "PROJECT ............................... " ${PROJECT_NAME})
message (STATUS "CMAKE_BINARY_DIR ...................... " ${CMAKE_BINARY_DIR})
message (STATUS "TM_MAIN_SOURCE_DIR .................... " ${TM_MAIN_SOURCE_DIR})
message (STATUS "CMAKE_GENERATOR ....................... " ${CMAKE_GENERATOR})
message (STATUS "CMAKE_C_COMPILER_ID ................... " ${CMAKE_C_COMPILER_ID})
message (STATUS "BINARY DIRECTORY ...................... " ${BIN_DIR})
message (STATUS "LIB BIN DIRECTORY ..................... " ${LIBRARY_OUTPUT_PATH})

add_subdirectory(src)
add_subdirectory(tests)
