cmake_minimum_required(VERSION 2.6)

project(EZVisual)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_COMPILER g++)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o2 -pthread -g")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_package(OpenCV)
find_package(RapidJSON)

include_directories("include")
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${RapidJSON_INCLUDE_DIRS})

add_subdirectory("include")
add_subdirectory("src")
add_subdirectory("demo")

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
