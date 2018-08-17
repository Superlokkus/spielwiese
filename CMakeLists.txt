cmake_minimum_required(VERSION 3.0)
enable_testing()

find_package(Boost REQUIRED COMPONENTS unit_test_framework)
#find_package(Boost REQUIRED) doesnt show this problems
include_directories(${Boost_INCLUDE_DIR})

add_executable(general_tests general_tests.cpp)
target_link_libraries(general_tests ${Boost_LIBRARIES})
add_test(NAME general_tests COMMAND general_tests -m HRF -l warning --build_info)
