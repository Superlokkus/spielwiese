cmake_minimum_required(VERSION 3.0)
project(interface_lib VERSION 1.0)

set(interface_lib_source_files
        RawDataStream.h
        RawDataStreamImplementation.hpp
        )

add_library(interface_lib INTERFACE)

target_include_directories(interface_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
