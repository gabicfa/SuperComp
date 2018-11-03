project(crawler)
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)
SET(SEQ_FLAG "-O2")
SET(DIS_FLAG "-O2")
SET(PAR_FLAG "-O2")

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

find_package(PkgConfig REQUIRED)
# Find SDL2

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_gfx REQUIRED SDL2_gfx)

#Add MPI
FIND_PACKAGE(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

# Add global definitions
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_gfx_INCLUDE_DIR})

add_executable(crawlerSEQ crawlerSequencial.cpp)
target_link_libraries(crawlerSEQ ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES} "-lcurl -lboost_regex")
SET_TARGET_PROPERTIES(crawlerSEQ PROPERTIES COMPILE_FLAGS ${SEQ_FLAG} LINK_FLAGS ${SEQ_FLAG})

add_executable(crawlerPAR crawlerParalelo.cpp)
target_link_libraries(crawlerPAR ${SDL2_LIBRARIES} ${SDL2_gfx_LIBRARIES} "-lcurl -lboost_regex -lpthread")
SET_TARGET_PROPERTIES(crawlerPAR PROPERTIES COMPILE_FLAGS ${PAR_FLAG} LINK_FLAGS ${PAR_FLAG})

add_executable(crawlerDIS crawlerDistribuido.cpp)
target_link_libraries(crawlerDIS ${SDL2_LIBRARIES} ${MPI_LIBRARIES} ${SDL2_gfx_LIBRARIES} "-lcurl -lboost_regex -lboost_mpi -lboost_serialization")
SET_TARGET_PROPERTIES(crawlerDIS PROPERTIES COMPILE_FLAGS ${SEQ_FLAG} LINK_FLAGS ${SEQ_FLAG})