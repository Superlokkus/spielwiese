cmake_minimum_required(VERSION 3.0)
enable_testing()


add_executable(general_tests general_tests.cpp)
set_property(TARGET general_tests PROPERTY CXX_STANDARD 14)
target_link_libraries(general_tests ${Boost_LIBRARIES} interface_lib)
add_test(NAME general_tests COMMAND general_tests -m HRF -l warning --build_info)
