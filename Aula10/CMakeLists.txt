cmake_minimum_required(VERSION 3.9)
project(projeto_basico)
set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.56 REQUIRED COMPONENTS filesystem)
find_package(OpenMP)
add_executable(exefs exemplo-fs.cpp)
add_executable(exsomp exemplo-fs.cpp)
target_link_libraries(exefs Boost::filesystem OpenMP::OpenMP_CXX)
target_link_libraries(exsomp Boost::filesystem)



