cmake_minimum_required(VERSION 3.15)

add_subdirectory(core)

add_executable(photomakerapp main.cpp )
target_link_libraries(photomakerapp photomakerapp_core_lib)
