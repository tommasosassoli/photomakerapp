cmake_minimum_required(VERSION 3.15)
project(photomakerapp)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(core)
include_directories(../test)

add_executable(photomakerapp main.cpp )
target_link_libraries(photomakerapp photomakerapp_core_lib)
