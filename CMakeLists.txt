cmake_minimum_required(VERSION 3.12)
project(colorGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCL REQUIRED)

add_executable (testOpenCL vecadd.cpp)

add_executable(colorGame
        main.cpp
        Universe.cpp
        Universe.h)

add_executable(testGame
        test/test.cpp
        test/catch.hpp
        Universe.h
        Universe.cpp)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(colorGame ${OPENCL_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} OpenCL)
TARGET_LINK_LIBRARIES(testOpenCL OpenCL)