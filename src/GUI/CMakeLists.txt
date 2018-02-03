cmake_minimum_required(VERSION 3.0.2)

project(TsunamiMaster)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH $ENV{QT_ROOT})

find_package(Qt5Quick)
find_package(Qt5Qml)
find_package(Qt5Gui)
find_package(Qt5Widgets)

file(GLOB TMGUI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB TMGUI_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB TMGUI_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/qml.qrc)

include_directories(${Qt5Gui_INCLUDE_DIRS}
					${Qt5Qml_INCLUDE_DIRS}
					${Qt5Quick_INCLUDE_DIRS}
					${COMMON_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${TMGUI_SRC} 
							   ${TMGUI_HEADER}
							   ${TMGUI_RESOURCES})

link_directories(${LIBRARY_OUTPUT_PATH})

add_dependencies(${PROJECT_NAME} TMlib)
add_dependencies(${PROJECT_NAME} TsunamiManager)

target_link_libraries(${PROJECT_NAME}	TsunamiManager
										TMlib
										Qt5::Widgets
										Qt5::Gui
										Qt5::Quick
										Qt5::Qml)


