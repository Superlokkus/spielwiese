cmake_minimum_required(VERSION 3.0)
project(lib_name2 VERSION 1.0)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER_CASE)
configure_file(
        ${PROJECT_NAME}_version.hpp.in
        ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/${PROJECT_NAME}_version.hpp
)

set(${PROJECT_NAME}_implementation_files
        src/lib.cpp
        )


add_library(${PROJECT_NAME} ${${PROJECT_NAME}_implementation_files})
set_property(TARGET ${PROJECT_NAME} PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

install(TARGETS ${PROJECT_NAME}
        ARCHIVE
        DESTINATION lib)
install(TARGETS ${PROJECT_NAME}
        PUBLIC_HEADER
        DESTINATION include)




