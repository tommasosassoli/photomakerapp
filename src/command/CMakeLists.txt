cmake_minimum_required(VERSION 3.15)

set(SOURCE_FILES
        Command.h
        CommandHandler.h CommandHandler.cpp
        FlipCommand.h
        MirrorCommand.h)

add_library(photomakerapp_command_lib ${SOURCE_FILES})