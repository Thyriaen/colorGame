cmake_minimum_required(VERSION 3.12)
project(vulkanTutorial)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(Vulkan REQUIRED)

include_directories(.)
include_directories(test)

add_executable(vulkanTutorial
        main.cpp
        Point.cpp
        Point.h
        Universe.cpp
        Universe.h)

target_link_libraries(vulkanTutorial Vulkan::Vulkan glfw)