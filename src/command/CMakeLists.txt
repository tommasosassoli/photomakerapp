cmake_minimum_required(VERSION 3.15)

set(SOURCE_FILES
        Command.h
        CommandHandler.h CommandHandler.cpp
        CropCommand.h
        FlipCommand.h
        MirrorCommand.h
        AdjustHueCommand.h
        AdjustSaturationCommand.h
        AdjustValueCommand.h
        BlurCommand.h
        SharpenCommand.h
        LaplacianCommand.h
        GrayscaleCommand.h
        BinaryCommand.h
        NegativeCommand.h
        )

add_library(photomakerapp_command_lib ${SOURCE_FILES})