#ifndef LIB_NAME_HPP
#define LIB_NAME_HPP

#include <lib_name/lib_name_version.hpp>

namespace lib_name {
    inline extern const struct statc_t {
        statc_t() {
            i = 0.905;
        }

        double i;
    } instance{};

    struct lib {
        double foo();
    };

}


#endif
