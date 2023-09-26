cmake_minimum_required(VERSION 3.21)
project(physics-engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)

find_package(daxa CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(simdjson CONFIG REQUIRED)
find_package(fastgltf CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_executable(physics-engine 
    src/main.cpp 
    src/physics/body.cpp 
    src/physics/scene.cpp
    src/physics/intersect.cpp
    src/app/app.cpp
    src/app/camera.cpp
    src/app/window.cpp
    src/app/model.cpp
    src/app/texture.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE daxa::daxa)
target_link_libraries(${PROJECT_NAME} PRIVATE fastgltf::fastgltf)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
