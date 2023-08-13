cmake_minimum_required(VERSION 3.18)

project(Astral)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/include/Astral/*.h ${CMAKE_SOURCE_DIR}/include/Astral/*.h)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_library(Astral ${SOURCES})

target_include_directories(Astral PUBLIC
    ${CMAKE_SOURCE_DIR}/include/Astral
)
target_include_directories(Astral SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/external
)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/argparse)

add_subdirectory(renderer)