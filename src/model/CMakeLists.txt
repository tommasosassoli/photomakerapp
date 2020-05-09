cmake_minimum_required(VERSION 3.15)

set(SOURCE_FILES
        AbstractPixel.cpp AbstractPixel.h
        RGBPixel.cpp RGBPixel.h
        HSVPixel.cpp HSVPixel.h
        Image.h
        KernelMatrix.cpp KernelMatrix.h)

add_library(photomakerapp_model_lib ${SOURCE_FILES})
