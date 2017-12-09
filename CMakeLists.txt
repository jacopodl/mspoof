cmake_minimum_required(VERSION 2.8)
project(LibArgsX)

set (VERSION_MAJOR 1)
set(VERSION_MINOR 7)
set(VERSION_PATCH 0)

set(ARGSX_USE_STATIC_LIB ON)

set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include")

add_subdirectory(src)
