#include <napi.h>

#include <lib_name/lib_name.hpp>


Napi::Number Method(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    lib_name::lib l;
    return Napi::Number::New(env, l.foo());
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "hello"),
                Napi::Function::New(env, Method));
    return exports;
}

NODE_API_MODULE(spielwiese, Init)