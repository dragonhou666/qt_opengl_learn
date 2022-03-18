cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(opengl_view)

set (TARGET_NAME ${CMAKE_PROJECT_NAME}${SUFFIX_STR})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-Wno-misleading-indentation -fexceptions)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/form)

find_package(Qt5 COMPONENTS Core Gui OpenGL Widgets REQUIRED)

file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE SRC_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/window.cpp"
    )

set(publish_bin_debug ${CMAKE_CURRENT_SOURCE_DIR}/../bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${publish_bin_debug})

add_executable(${PROJECT_NAME} 
    ${HEADER_FILES}
    ${SRC_FILES}
)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/include")

link_directories(${PROJECT_SOURCE_DIR}/lib/debug)

target_link_libraries(${PROJECT_NAME}
    opengl_draw
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::OpenGL
)

