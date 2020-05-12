cmake_minimum_required(VERSION 3.15)

#Qt5 init
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++11")

find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

#Project libraries
add_subdirectory(model)
add_subdirectory(core)
add_subdirectory(utils)
add_subdirectory(view)

#Executable
add_executable(photomakerapp main.cpp)

#Linking libraries
target_link_libraries(photomakerapp
        Qt5::Widgets
        photomakerapp_model_lib
        photomakerapp_core_lib
        photomakerapp_utils_lib
        photomakerapp_views_lib)

set_target_properties(photomakerapp
        photomakerapp_model_lib
        photomakerapp_core_lib
        photomakerapp_utils_lib
        photomakerapp_views_lib

        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/photomakerapp/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/photomakerapp")