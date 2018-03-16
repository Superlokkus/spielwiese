cmake_minimum_required(VERSION 3.0)
project(CPP_Spielwiese)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(PROJECT_SOURCE_DIR src)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib_name)

add_subdirectory(${PROJECT_SOURCE_DIR}/interface_lib)

add_executable(main ${PROJECT_SOURCE_DIR}/main.cpp)

set_property(TARGET main PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET main PROPERTY CXX_STANDARD 14)

target_link_libraries(main interface_lib)
target_link_libraries(main lib_name)

enable_testing()
add_subdirectory(test)