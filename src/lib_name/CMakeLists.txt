cmake_minimum_required(VERSION 3.0)
project(lib_name VERSION 1.0)

set(lib_name_implementation_files
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib.cpp
        )


add_library(lib_name ${lib_name_implementation_files})
set_property(TARGET lib_name PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET lib_name PROPERTY CXX_STANDARD 14)

target_include_directories(lib_name PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
