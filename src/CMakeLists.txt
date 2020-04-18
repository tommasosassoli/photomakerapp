cmake_minimum_required(VERSION 3.15)

add_subdirectory(utils)
add_subdirectory(core)

add_executable(photomakerapp main.cpp)

target_link_libraries(photomakerapp photomakerapp_core_lib photomakerapp_utils_lib)

set_target_properties(photomakerapp photomakerapp_core_lib photomakerapp_utils_lib
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/photomakerapp/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/photomakerapp")