project(visualizador)
cmake_minimum_required(VERSION 2.8)

message("STRATEGY: $ENV{STRATEGY}")

if("$ENV{STRATEGY}" MATCHES "omp")
    set (CMAKE_CXX_FLAGS "-std=c++11 -fopenmp -lpthread -O2")

elseif("$ENV{STRATEGY}" MATCHES "simd")
    set (CMAKE_CXX_FLAGS "-std=c++11 -ffast-math -ftree-vectorize -mavx2 -O2")

elseif("$ENV{STRATEGY}" MATCHES "seq")
    set (CMAKE_CXX_FLAGS "-std=c++11")

else()
    set (CMAKE_CXX_FLAGS "-std=c++11 -fopenmp -lpthread -O2")
    
endif()

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

find_package(PkgConfig REQUIRED)
# Find SDL2

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_gfx REQUIRED SDL2_gfx)

# Add global definitions
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_gfx_INCLUDE_DIR})

add_executable(visualizador main.cpp visualizador.cpp)
target_link_libraries(visualizador ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})
