project(scene1)

add_executable(test main.cpp)

target_link_libraries(test PUBLIC Astral)

target_include_directories(test PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(test SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(ASSET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
configure_file(config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp)