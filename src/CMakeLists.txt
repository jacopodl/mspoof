cmake_minimum_required(VERSION 2.8)
project(LibArgsX)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --pedantic")
configure_file("${PROJECT_SOURCE_DIR}/argsx.h" "${INCLUDE_PATH}/argsx.h")

if (ARGSX_USE_STATIC_LIB)
    add_library(ArgsX STATIC argsx.c)
else ()
    add_library(ArgsX SHARED argsx.c)
endif ()