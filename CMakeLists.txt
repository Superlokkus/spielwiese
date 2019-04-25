cmake_minimum_required(VERSION 3.0)
project(CPP_Spielwiese VERSION 1.0)

set(TEST_ENABLED TRUE CACHE BOOL "Tests are enabled")
if (${TEST_ENABLED})
    enable_testing()
endif ()

add_subdirectory(${PROJECT_SOURCE_DIR}/src/lib_name)

add_executable(${PROJECT_NAME} src/main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} PRIVATE lib_name)

if (${TEST_ENABLED})
    find_package(Boost COMPONENTS system REQUIRED)
    set(${PROJECT_NAME}_test_src
            ${CMAKE_CURRENT_SOURCE_DIR}/test/general_tests.cpp
            )
    foreach (testSrc ${${PROJECT_NAME}_test_src})
        get_filename_component(testName ${testSrc} NAME_WE)
        add_executable(${PROJECT_NAME}_${testName} ${testSrc})
        set_property(TARGET ${PROJECT_NAME}_${testName} PROPERTY CXX_STANDARD 14)
        target_link_libraries(${PROJECT_NAME}_${testName} Boost::boost lib_name)
        add_test(NAME ${PROJECT_NAME}_${testName} COMMAND ${PROJECT_NAME}_${testName} -m HRF -l warning --build_info)
    endforeach (testSrc)
endif ()

