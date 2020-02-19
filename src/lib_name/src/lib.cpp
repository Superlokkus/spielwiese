#include <lib.hpp>
#include <iostream>



double lib_name::lib::foo() {
    return foo2();
}

double foo2() {
    std::cout << "FOO " << lib_name::instance.i << std::endl;
    return lib_name::instance.i;
}
