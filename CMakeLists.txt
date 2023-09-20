cmake_minimum_required(VERSION 3.26)
project(physics_engine)

set(CMAKE_CXX_STANDARD 20)

# Find the Eigen3 package
find_package(Eigen3 REQUIRED)

# Function to add a chapter with executables
function(add_chapter chapter_name)
    set(options EXECUTABLE)
    set(oneValueArgs SOURCES)
    cmake_parse_arguments(ADD_CHAPTER "${options}" "" "${oneValueArgs}" ${ARGN})

    if(ADD_CHAPTER_EXECUTABLE)
        add_executable(${chapter_name} ${ADD_CHAPTER_SOURCES})
        target_link_libraries(${chapter_name} PRIVATE Eigen3::Eigen)
    endif()
endfunction()

# Add your chapters using the function
add_chapter(physics-engine
        SOURCES main.cpp Math/math.hpp
        EXECUTABLE
)