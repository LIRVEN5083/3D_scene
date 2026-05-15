cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(PROJECT_NAME MyProject)
project (${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} 
    Sources/main.cpp

    Sources/BaseFunctions.cpp
    "Sources/BaseFunctions.hpp"

    Sources/Renderer/ShaderProgram.cpp
    "Sources/Renderer/ShaderProgram.hpp"

    "Sources/Renderer/GLSL_files/load_GLSL.hpp"
    "Sources/Renderer/GLSL_files/load_GLSL.cpp"

    "Sources/Matrix/Matrix.hpp"
    "Sources/Matrix/Matrix.cpp"

    "Sources/Matrix/liniarMath.hpp"
    "Sources/Matrix/liniarMath.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE Sources/Matrix)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build tests" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build docs" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "Install GLFW" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

