cmake_minimum_required(VERSION 3.30)
project(ShitAssNeuralNetworkFramework)

set(CMAKE_CXX_STANDARD 23)

add_executable(ShitAssNeuralNetworkFramework main.cpp)
add_library(SANNF_Lib SHARED SANNF.cpp SANNF.hpp)

link_libraries(ShitAssNeuralNetworkFramework SANNF_Lib)
