#ifndef SPIELWIESE_PROMISE_METHOD_HPP
#define SPIELWIESE_PROMISE_METHOD_HPP

#include <napi.h>

#include "promise_worker.hpp"

struct PromiseMethodWorker : PromiseWorker {
    PromiseMethodWorker(Napi::Promise::Deferred const &d, int input)
            : PromiseWorker(d), input_{std::move(input)} {}

    void Resolve(Napi::Promise::Deferred const &deferred) override {
        deferred.Resolve(create_js(deferred.Env()));
    }

    void Execute() override {
        output_ = input_ * 5;
    }

private:
    int input_;
    int output_;

    Napi::Number create_js(Napi::Env env) const {
        Napi::Number js_value = Napi::Number::New(env, output_);
        return js_value;
    }

};

Napi::Promise PromiseMethod(const Napi::CallbackInfo &info) {
    int input = info[0].ToNumber();

    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());

    auto *wk = new PromiseMethodWorker(deferred, input);
    wk->Queue();

    return deferred.Promise();
}


#endif //SPIELWIESE_PROMISE_METHOD_HPP
