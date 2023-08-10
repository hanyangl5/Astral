cmake_minimum_required(VERSION 3.18)

project(Astral)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/include/Astral/*.h ${CMAKE_SOURCE_DIR}/include/Astral/*.h)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.cpp)

#add_library(${PROJECT_NAME} ${SOURCES})

add_subdirectory(config)

add_executable(test test/main.cpp)

target_include_directories(test PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/config
)

target_include_directories(test SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/external
)