//
// Created by Markus Klemm on 14.03.18.
//

#ifndef CPP_SPIELWIESE_LIB_HPP
#define CPP_SPIELWIESE_LIB_HPP

#include <nan.h>

NAN_METHOD(CalculateSync);

NAN_MODULE_INIT(Init) {
    Nan::Set(target, Nan::New<v8::String>("calculateSync").ToLocalChecked(),
        Nan::GetFunction(Nan::New<v8::FunctionTemplate>(CalculateSync)).ToLocalChecked());
}

NODE_MODULE(lib_name, Init)

#endif //CPP_SPIELWIESE_LIB_HPP
