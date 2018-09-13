cmake_minimum_required(VERSION 3.9)
project(projeto_basico)
set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.56 REQUIRED COMPONENTS filesystem)
add_executable(exemplo_fs exemplo_fs.cpp)
target_link_libraries(exemplo_fs Boost::filesystem)

find_package(OpenMP)
add_executable(teste_omp teste_omp.cpp)
target_link_libraries(teste_omp OpenMP::OpenMP_CXX)


