cmake_minimum_required(VERSION 3.26)
project(physics-engine)

set(CMAKE_CXX_STANDARD 23)

# Find the Eigen3 package
find_package(Eigen3 REQUIRED)

add_executable(physics-engine main.cpp Physics/Body.hpp Physics/Scene.hpp Physics/Shape.hpp)


target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen)