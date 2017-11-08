cmake_minimum_required(VERSION 3.7)
project(gridlight_rast)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES main.cpp model/Model.cpp model/Model.h math/Vector3.cpp math/Vector3.h math/Vector4.cpp math/Vector4.h math/Matrix4.cpp math/Matrix4.h math/Vector2.cpp math/Vector2.h math/Matrix3.cpp math/Matrix3.h)
add_executable(gridlight_rast ${SOURCE_FILES})


SET( CMAKE_CXX_FLAGS '-llua')
include_directories("include/")
find_package(Lua51 REQUIRED)
file(GLOB SOURCES
        include/*.h
        include/*.c
        include/*.cpp
        include/*.h
        include/*.cpp
        )

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})