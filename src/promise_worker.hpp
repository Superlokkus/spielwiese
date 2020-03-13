#ifndef SPIELWIESE_PROMISE_WORKER_HPP
#define SPIELWIESE_PROMISE_WORKER_HPP

#include <napi.h>

class PromiseWorker : public Napi::AsyncWorker {
public:
    PromiseWorker(Napi::Promise::Deferred const &d) : AsyncWorker(get_fake_callback(d.Env()).Value()), deferred(d) {}

    virtual void Resolve(Napi::Promise::Deferred const &deferred) = 0;

    void OnOK() override {
        Resolve(deferred);
    }

    void OnError(Napi::Error const &error) override {
        deferred.Reject(error.Value());
    }

private:
    static Napi::Value noop(Napi::CallbackInfo const &info) {
        return info.Env().Undefined();
    }

    Napi::Reference<Napi::Function> const &get_fake_callback(Napi::Env const &env) {
        static Napi::Reference<Napi::Function> fake_callback
                = Napi::Reference<Napi::Function>::New(Napi::Function::New(env, noop), 1);
        fake_callback.SuppressDestruct();

        return fake_callback;
    }

    Napi::Promise::Deferred deferred;
};


#endif //SPIELWIESE_PROMISE_WORKER_HPP
