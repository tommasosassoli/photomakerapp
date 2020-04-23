cmake_minimum_required(VERSION 3.15)

set(SOURCE_FILES
        Image.h
        pixels/RGBPixel.cpp pixels/RGBPixel.h
        ImageException.h
        ImageProcessor.cpp ImageProcessor.h
        KernelTemplate.cpp KernelTemplate.h
        pixels/HSVPixel.cpp pixels/HSVPixel.h
        KernelMatrix.cpp KernelMatrix.h
        pixels/AbstractPixel.cpp pixels/AbstractPixel.h)

add_library(photomakerapp_core_lib ${SOURCE_FILES})
