#include <lib.hpp>
#include <lib_name2/lib_name.hpp>

int lib_name::lib::foo() {
    return foo2();
}

int foo2() {
    return lib_name2::lib().foo();
}
