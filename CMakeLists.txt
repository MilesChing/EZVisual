cmake_minimum_required(VERSION 2.6)

project(EZVisual)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_COMPILER g++)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -pthread")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

include_directories("include")
add_subdirectory("src")
add_subdirectory("test")