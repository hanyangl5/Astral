project(scene1)

add_executable(scene1 main.cpp)

target_link_libraries(scene1 PUBLIC Astral)

target_include_directories(scene1 PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(scene1 SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(ASSET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
configure_file(config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp)