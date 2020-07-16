cmake_minimum_required(VERSION 3.15)

set( SCRIPT_FILES photomakerapp.sh)


file( COPY ${SCRIPT_FILES} DESTINATION "${CMAKE_BINARY_DIR}/bin/photomakerapp")