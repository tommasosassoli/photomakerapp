cmake_minimum_required(VERSION 3.15)

set(SOURCE_FILES
        KernelTemplate.h
        KernelTemplate.cpp
        ViewUtils.cpp)

add_library(photomakerapp_utils_lib ${SOURCE_FILES})
