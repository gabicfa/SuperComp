project(visualizador)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)

SET(SIMD_FLAG "-ffast-math -ftree-vectorize -mavx2 -O2")
SET(OMP_FLAG "-fopenmp -lpthread -O2")
SET(SEQ_FLAG "-O2")

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

find_package(PkgConfig REQUIRED)
# Find SDL2

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_gfx REQUIRED SDL2_gfx)

# Add global definitions
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_gfx_INCLUDE_DIR})

add_executable(visualizadorOMP main.cpp visualizador.cpp)
target_link_libraries(visualizadorOMP ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})
SET_TARGET_PROPERTIES(visualizadorOMP PROPERTIES COMPILE_FLAGS ${OMP_FLAG} LINK_FLAGS ${OMP_FLAG})

add_executable(visualizadorSIMD main.cpp visualizador.cpp)
target_link_libraries(visualizadorSIMD ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})
SET_TARGET_PROPERTIES(visualizadorSIMD PROPERTIES COMPILE_FLAGS ${SIMD_FLAG} LINK_FLAGS ${SIMD_FLAG})

add_executable(visualizadorSEQ main.cpp visualizador.cpp)
target_link_libraries(visualizadorSEQ ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES})
SET_TARGET_PROPERTIES(visualizadorSEQ PROPERTIES COMPILE_FLAGS ${SEQ_FLAG} LINK_FLAGS ${SEQ_FLAG})