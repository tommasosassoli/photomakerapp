cmake_minimum_required(VERSION 3.15)

#copy icons folder into build-debug folder

set( RESOURCE_FILES
        crop.svg
        color.svg
        filter.svg
        open.svg
        save.svg
        redo.svg
        undo.svg
)

file( COPY ${RESOURCE_FILES} DESTINATION "${CMAKE_BINARY_DIR}/bin/photomakerapp/resources")