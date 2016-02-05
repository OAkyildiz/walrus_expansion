## BEGIN_TUTORIAL
## This CMakeLists.txt file for rviz_plugin_tutorials builds both the TeleopPanel tutorial and the ImuDisplay tutorial.
##
## First start with some standard catkin stuff.
cmake_minimum_required(VERSION 2.8.3)
project(walrus_widget)
find_package(catkin REQUIRED COMPONENTS rviz roscpp)
#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)


catkin_package()
include_directories(${catkin_INCLUDE_DIRS}  
#${GLUT_INCLUDE_DIRS} 
#${OpenGL_INCLUDE_DIRS}
${PROJECT_BINARY_DIR}
include)

link_directories(${catkin_LIBRARY_DIRS} 
#${GLUT_LIBRARY_DIRS}  
#${OpenGL_LIBRARY_DIRS}
 )


## This plugin includes Qt widgets, so we must include Qt like so:
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL QtDesigner REQUIRED )
SET(QT_USE_QTOPENGL TRUE)

include(${QT_USE_FILE})

## I prefer the Qt signals and slots to avoid defining "emit", "slots",
## etc because they can conflict with boost signals, so define QT_NO_KEYWORDS here.
add_definitions(-DQT_NO_KEYWORDS)

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
  include/walrus_widget/*.hpp
  include/walrus_widget/*.h
  /*.h
  /*.hpp
)
list(REMOVE_ITEM HDR_FILES "include/walrus_widget/scene.h")

file(GLOB CPP_FILES   
  src/*.cpp
)
list(REMOVE_ITEM CPP_FILES "src/scene.cpp")

## Add the "myviz" executable and specify the list of source files we
## collected above in ``${SRC_FILES}``.

#qt4_add_resources(MOC_RES ${RES_FILES})
qt4_wrap_ui(MOC_UI ${UI_FILES})

qt4_wrap_cpp(MOC_FILES
  ${HDR_FILES}
)
##
#qt4_wrap_ui
#qt4_add_resources

add_executable(widget ${CPP_FILES} ${MOC_FILES} ${MOC_UI} )

## Link the myviz executable with whatever Qt libraries have been defined by
## the ``find_package(Qt4 ...)`` line above, and with whatever libraries
## catkin has included.
target_link_libraries(widget ${QT_LIBRARIES} 
#${GLUT_LIBRARIES} 
#${OPENGL_LIBRARIES} 
${catkin_LIBRARIES}
 )
## END_TUTORIAL

## Install
install(TARGETS widget DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
