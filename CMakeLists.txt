cmake_minimum_required(VERSION 3.26)
project(physics-engine)

set(CMAKE_CXX_STANDARD 23)

add_executable(physics-engine main.cpp physics/body.cpp physics/scene.cpp)