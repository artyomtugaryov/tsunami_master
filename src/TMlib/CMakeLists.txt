cmake_minimum_required(VERSION 2.8)

project("TMlib")

file(GLOB TMLIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB TMLIB_HEADERS ${COMMON_INCLUDE_DIR}/TMlib/*.h)

include_directories(${COMMON_INCLUDE_DIR})

add_library(${PROJECT_NAME} SHARED ${TMLIB_SRC} ${TMLIB_HEADERS})
