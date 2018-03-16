#include <iostream>
#include <interface_lib.hpp>
#include <lib.hpp>

int main() {
    lib a;
    std::cout << a.foo() << std::endl;
    return 0;
}