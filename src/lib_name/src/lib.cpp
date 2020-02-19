#include <lib.hpp>

double lib_name::lib::foo() {
    return foo2();
}

double foo2() {
    return static_map.at(1.15).at(44);
}
