cmake_minimum_required(VERSION 2.8.13)

project("using_iterators")

cmake_policy(SET CMP0054 NEW)

file(GLOB UITRS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB UITRS_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

include_directories(${COMMON_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${UITRS_SRC} ${UITRS_HEADERS})

add_dependencies(${PROJECT_NAME} TMlib)

target_link_libraries(${PROJECT_NAME} TMlib)
