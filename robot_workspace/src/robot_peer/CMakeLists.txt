cmake_minimum_required(VERSION 2.8.3)
project(robot_peer)

## Add c++11 compile option
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
 	roscpp
	rqt_gui_cpp
)

## System dependencies are found with CMake's conventions

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
	find_package(Qt5Network REQUIRED)
	find_package(Qt5Widgets REQUIRED)
else()
	find_package(Qt4 COMPONENTS QtCore QtGui QtNetwork REQUIRED)
	include(${QT_USE_FILE})
endif()

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
	INCLUDE_DIRS include
	LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS roscpp rqt_gui_cpp
)


set (${PROJECT_NAME}_SRCS
	src/${PROJECT_NAME}/robot_peer.cpp
)

set(${PROJECT_NAME}_HDRS
	include/${PROJECT_NAME}/robot_peer.h
)

set(${PROJECT_NAME}_UIS
	ui/${PROJECT_NAME}/robot_peer.ui
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
	qt5_wrap_cpp(${PROJECT_NAME}_MOCS ${${PROJECT_NAME}_HDRS})
	qt5_wrap_ui(${PROJECT_NAME}_UIS_H ${${PROJECT_NAME}_UIS})
else()
	qt4_wrap_cpp(${PROJECT_NAME}_MOCS ${${PROJECT_NAME}_HDRS})
	qt4_wrap_ui(${PROJECT_NAME}_UIS_H ${${PROJECT_NAME}_UIS})
endif()

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
	include
	${CMAKE_CURRENT_BINARY_DIR}/..
	${catkin_INCLUDE_DIRS}
)

## Declare a cpp library
add_library(${PROJECT_NAME}
	${${PROJECT_NAME}_SRCS}
	${${PROJECT_NAME}_MOCS}
	${${PROJECT_NAME}_UIS_H}
)

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
	${catkin_LIBRARIES}
)

if("${qt_gui_cpp_USE_QT_MAJOR_VERSION} " STREQUAL "5 ")
	target_link_libraries(${PROJECT_NAME} Qt5::Network Qt5::Widgets)
else()
	target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY})
endif()