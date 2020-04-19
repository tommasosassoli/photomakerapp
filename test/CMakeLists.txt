cmake_minimum_required(VERSION 3.15)

add_subdirectory(lib/googletest)
set(GTEST_SOURCE_DIR, ./lib/googletest)
include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

set(SOURCE_FILES
        mainTestPhotoMakerApp.cpp
        TestSquareImage.cpp
        TestRectangleImage.cpp
        TestPixelMatrix.cpp
        TestImageProcessor.cpp
        TestExecutionTime.cpp TestPixelConversion.cpp)

add_executable(runTestPhotoMakerApp ${SOURCE_FILES})
target_link_libraries(runTestPhotoMakerApp
        gtest gtest_main
        photomakerapp_core_lib)