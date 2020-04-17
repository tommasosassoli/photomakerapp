cmake_minimum_required(VERSION 3.15)

add_subdirectory(lib/googletest)
set(GTEST_SOURCE_DIR, ./lib/googletest)
include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

set(SOURCE_FILES mainTestKernelImage.cpp TestSquareImage.cpp TestRectangleImage.cpp TestPixelMatrix.cpp TestImageProcessor.cpp TestExecutionTime.cpp)
add_executable(runTestKernelImage ${SOURCE_FILES})
target_link_libraries(runTestKernelImage gtest gtest_main kernelImage_lib)