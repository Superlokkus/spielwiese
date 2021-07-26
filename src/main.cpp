#include <lib_name/lib_name.hpp>

int main() {
    myWeb::Website site("https://www.markusklemm.net");
    std::cout << site.get("/", 1024) << "\n";
}
