cmake_minimum_required(VERSION 3.15)

set(SOURCE_FILES
        ImageException.h
        ImageProcessor.cpp)

add_library(photomakerapp_core_lib ${SOURCE_FILES})
