#define BOOST_TEST_MODULE My Test

#include <boost/test/included/unit_test.hpp>

#include <lib_name/lib_name.hpp>


BOOST_AUTO_TEST_CASE(FIRST_TEST) {
    BOOST_CHECK_EQUAL(lib_name::lib{}.foo(), 5);
}



