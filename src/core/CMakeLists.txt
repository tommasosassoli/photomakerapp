cmake_minimum_required(VERSION 3.15)

set(SOURCE_FILES
        Image.cpp Image.h
        Pixel.cpp Pixel.h
        ImageException.h
        PixelMatrix.cpp PixelMatrix.h
        ImageProcessor.cpp ImageProcessor.h
        KernelTemplate.cpp KernelTemplate.h)

add_library(photomakerapp_core_lib ${SOURCE_FILES})
