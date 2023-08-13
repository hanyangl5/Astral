function(configure_project project_name)
    project(${project_name})

    add_executable(${project_name} main.cpp)

    target_link_libraries(${project_name} PUBLIC Astral argparse)

    target_include_directories(${project_name} PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_include_directories(${project_name} SYSTEM PUBLIC
        ${CMAKE_SOURCE_DIR}/external
    )

    set(ASSET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
    configure_file(config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp)
endfunction()