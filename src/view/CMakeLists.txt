cmake_minimum_required(VERSION 3.15)

set(SOURCE_FILES
        MainView.h MainView.cpp
        MainViewWindow.h
        subwidgets/AbstractSheet.h
        subwidgets/LeftMenuBar.h
        subwidgets/CropSheet.h
        subwidgets/ColorSheet.h
        subwidgets/FilterSheet.h)

add_library(photomakerapp_views_lib ${SOURCE_FILES})
