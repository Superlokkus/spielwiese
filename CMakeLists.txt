cmake_minimum_required(VERSION 3.0)
project(CPP_Spielwiese)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(PROJECT_SOURCE_DIR src)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib_name)

add_subdirectory(${PROJECT_SOURCE_DIR}/interface_lib)

enable_testing()
add_subdirectory(test)