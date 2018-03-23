cmake_minimum_required(VERSION 3.0)
project(lib_name VERSION 1.0)

set(${PROJECT_NAME}_implementation_files
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib.cpp
        )


add_library(${PROJECT_NAME} ${${PROJECT_NAME}_implementation_files})
set_property(TARGET ${PROJECT_NAME} PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
