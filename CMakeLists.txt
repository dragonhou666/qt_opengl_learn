cmake_minimum_required(VERSION 3.5)

project(opengl_draw)

set (TARGET_NAME ${CMAKE_PROJECT_NAME}${SUFFIX_STR})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Gui OpenGL Widgets REQUIRED)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/include"
                     "${CMAKE_CURRENT_SOURCE_DIR}/source"
)

file(GLOB RESOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
                                "${CMAKE_CURRENT_SOURCE_DIR}/source/*.h")
file (GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

add_subdirectory(app)

set(publish_lib_debug ${CMAKE_CURRENT_SOURCE_DIR}/lib/debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${publish_lib_debug})

link_directories("/lib/x86_64-linux-gnu/")
link_libraries("GL")

add_library(${TARGET_NAME} STATIC
    ${HEADER_FILES}
    ${SRC_FILES}
    ${RESOURCE_FILES}
)

target_link_libraries(${TARGET_NAME}
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::OpenGL
    GL
    GLU
)



