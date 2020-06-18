cmake_minimum_required(VERSION 3.15)

add_subdirectory(lib/googletest)
set(GTEST_SOURCE_DIR, ./lib/googletest)
include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

set(SOURCE_FILES
        mainTestPhotoMakerApp.cpp
        TestImageProcessor.cpp
        TestExecutionTime.cpp
        TestPixelConversion.cpp
        TestUndoRedo.cpp)

add_executable(runTestPhotoMakerApp ${SOURCE_FILES})
target_link_libraries(runTestPhotoMakerApp
        gtest gtest_main
        photomakerapp_model_lib
        photomakerapp_core_lib
        photomakerapp_utils_lib)