#include <lib.hpp>

int lib_name::lib::foo() {
    return foo2();
}

int foo2() {
    return static_map.cbegin()->second;
}
