cmake_minimum_required(VERSION 3.10.0)
project(loop-subdivision VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

#include(conanfile.txt)
#conan_basic_setup()
#conan install . --output-folder=build
set(SOURCE
   source/main.cpp
   source/src/application.cpp
)
set(HEADERS
   source/include/application.h
)

add_subdirectory("source/solid-math")

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::GLEW)
else()
    message("Unable to find GLEW")
endif()

find_package(glfw3 REQUIRED)
if (glfw3_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
else()
    message("Unable to find glfw")
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC solid-math)
