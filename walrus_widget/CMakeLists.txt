## This CMakeLists.txt file for rviz_plugin_tutorials builds both the TeleopPanel tutorial and the ImuDisplay tutorial.
##
## First start with some standard catkin stuff.
cmake_minimum_required(VERSION 2.8.3)
#include(CheckCXXCompilerFlag)
#CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
#CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
#if(COMPILER_SUPPORTS_CXX11)
#    set(CMAKE_CXX_FLAGS "-std=c++11")
#elseif(COMPILER_SUPPORTS_CXX0X)
#    set(CMAKE_CXX_FLAGS "-std=c++0x")
#else()
#    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
#endif()

project(walrus_widget)
#Tell CMake to run moc when necessary:
#set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(qversion 5.5.1)
find_package(catkin REQUIRED COMPONENTS
roscpp rviz image_transport cv_bridge
#rtabmap_ros 
diagnostic_msgs nav_msgs visualization_msgs)

find_package(RTABMap 0.10.10 REQUIRED)
find_package(Qt5Widgets ${qversion} REQUIRED)
find_package(Qt5Gui ${qversion} REQUIRED)
find_package(Qt5Quick ${qversion} REQUIRED)

#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)


catkin_package()
include_directories(${catkin_INCLUDE_DIRS}
    ${RTABMap_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDES}
    ${Qt5Gui_INCLUDES}
    ${Qt5Quick_INCLUDES}
    #${GLUT_INCLUDE_DIRS}
    #${OpenGL_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR}
    include
)

#catkin_package
catkin_package(
   INCLUDE_DIRS include
   LIBRARIES ${PROJECT_NAME}
   CATKIN_DEPENDS nodelet rviz roscpp
   DEPENDS eigen opencv)

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})
add_definitions(${Qt5Quick_DEFINITIONS})

link_directories(
    ${catkin_LIBRARY_DIRS}
    ${RTABMap_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Quick_LIBRARIES}
    #${GLUT_LIBRARY_DIRS}
    #${OpenGL_LIBRARY_DIRS}
)


## This plugin includes Qt widgets, so we must include Qt like so:
SET(QT_USE_QTOPENGL TRUE)

##include(${QT_USE_FILE})

## I prefer the Qt signals and slots to avoid defining "emit", "slots",
## etc because they can conflict with boost signals, so define QT_NO_KEYWORDS here.
add_definitions(-DQT_NO_KEYWORDS)

include($ENV{ROS_ROOT}/core/rosbuild/FindPkgConfig.cmake)
pkg_check_modules(OGRE OGRE)
include_directories( ${OGRE_INCLUDE_DIRS} )
link_directories( ${OGRE_LIBRARY_DIRS} )
## Here we specify which header files need to be run through "moc",
## Qt's meta-object compiler.

## Here we specify the list of source files, including the output of
## the previous command which is stored in ``${MOC_FILES}``.


file(GLOB UI_FILES
  ui/*.ui
)

file(GLOB RES_FILES
  resources/*.qrc
)

file(GLOB HDR_FILES
  include/*/*.hpp
  include/*/*.h
  /*.h
  /*.
)
#message(STATUS "${HDR_FILES}")

list(REMOVE_ITEM HDR_FILES "include/walrus_widget/scene.h"
    "include/rtabmap_ros/rviz/InfoDisplay.h"
    "include/rtabmap_ros/rviz/MapCloudDisplay.h"
    "include/rtabmap_ros/rviz/MapGraphDisplay.h"
    "include/rtabmap_ros/rviz/OrbitOrientedView.h")

file(GLOB CPP_FILES
  src/*.cpp
)
list(REMOVE_ITEM CPP_FILES "src/scene.cpp"
        "src/rtabmap_ros/rviz/InfoDisplay.h"
        "src/rtabmap_ros/rviz/MapCloudDisplay.h"
        "src/rtabmap_ros/rviz/MapGraphDisplay.h"
        "src/rtabmap_ros/rviz/OrbitOrientedView.h")

## Add the "myviz" executable and specify the list of source files we
## collected above in ``${SRC_FILES}``.

#
#qt5_add_resources(MOC_RES   ${RES_FILES})
qt5_wrap_ui(MOC_UI ${UI_FILES})

qt5_wrap_cpp(MOC_FILES ${HDR_FILES})
##


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

add_executable(widget ${CPP_FILES} ${MOC_FILES} ${MOC_UI} )

## Link the myviz executable with whatever Qt libraries have been defined by
## the ``find_package(Qt4 ...)`` line above, and with whatever libraries
## catkin has included.
target_link_libraries(widget
    #${QT_LIBRARIES}
    ${RTABMap_LIBRARIES}
    #${GLUT_LIBRARIES}
    #${OPENGL_LIBRARIES}
    ${OGRE_LIBRARIES}
    ${catkin_LIBRARIES}
    Qt5::Widgets
    Qt5::Gui
    Qt5::Quick

 )

## Install
#install(TARGETS widget DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

#install(DIRECTORY include/${PROJECT_NAME}/
#  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#  FILES_MATCHING PATTERN "*.h"
#  FILES_MATCHING PATTERN "*.hpp"

#)

#install(DIRECTORY launch
#  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
#)
#install(DIRECTORY config
#  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
#)
