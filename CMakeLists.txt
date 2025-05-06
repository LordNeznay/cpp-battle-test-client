cmake_minimum_required(VERSION 3.27)
project(sw_battle_test)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

# Сохраняем структуру папок для Visual Studio
if(MSVC)
    foreach(source_file ${SOURCES})
        file(RELATIVE_PATH source_rel_path "${CMAKE_CURRENT_SOURCE_DIR}" "${source_file}")
        get_filename_component(source_path "${source_rel_path}" PATH)

        string(REPLACE "/" "\\" group_name "${source_path}")
        source_group("${group_name}" FILES "${source_file}")
    endforeach()
endif()

add_executable(sw_battle_test ${SOURCES})

target_include_directories(sw_battle_test PUBLIC src/)
