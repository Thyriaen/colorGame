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
TARGET_LINK_LIBRARIES(colorGame ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

TARGET_LINK_LIBRARIES(testGame ${SDL2_LIBRARIES})


#TARGET_LINK_LIBRARIES(colorGame ${OPENCL_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} OpenCL)
#TARGET_LINK_LIBRARIES(testOpenCL OpenCL)