#include <napi.h>

#include <lib_name/lib_name.hpp>


Napi::String Method(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, "world");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    lib_name::lib l;
    exports.Set(Napi::Number::New(env, l.foo()),
                Napi::Function::New(env, Method));
    return exports;
}

NODE_API_MODULE(spielwiese, Init)