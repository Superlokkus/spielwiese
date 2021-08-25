#include <lib.hpp>

namespace lib_name2{

    int lib_name2::lib::foo() {
        return foo2();
    }

    int foo2() {
        return 5;
    }

}
