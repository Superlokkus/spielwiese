//
// Created by Markus Klemm on 14.03.18.
//

#include <lib.hpp>

NAN_METHOD(CalculateSync) {
    // expect a number as the first argument
    int points = info[0]->Uint32Value();
    double est = points*5;

    info.GetReturnValue().Set(est);
}
