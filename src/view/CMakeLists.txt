cmake_minimum_required(VERSION 3.15)

set(SOURCE_FILES
        Subject.h
        Observer.h
        ImageWrapper.h ImageWrapper.cpp
        MainViewController.h MainViewController.cpp
        MainView.h MainView.cpp
        MainViewWindow.h
        subwidgets/AbstractSheet.h
        subwidgets/CropSheet.h
        subwidgets/ColorSheet.h
        subwidgets/FilterSheet.h
        subwidgets/TopMenuBar.h
        subwidgets/RenderArea.h subwidgets/RenderArea.cpp)

add_library(photomakerapp_views_lib ${SOURCE_FILES})
