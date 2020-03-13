#include <napi.h>

#include <lib_name/lib_name.hpp>

#include "promise_method.hpp"

Napi::String Method(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, "world");
}


Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "hello"),
                Napi::Function::New(env, Method));
    exports.Set(Napi::String::New(env, "PromiseMethod"),
                Napi::Function::New(env, PromiseMethod));

    return exports;
}

NODE_API_MODULE(spielwiese, Init)