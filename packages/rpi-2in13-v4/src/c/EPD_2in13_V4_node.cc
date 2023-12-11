#include "napi.h"
extern "C" {
    #include "DEV_Config.h"
    #include "EPD_2in13_V4.h"
}

Napi::Number DEV_Init(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    uint8_t result = DEV_ModuleInit();
    return Napi::Number::New(env, result);
}

Napi::Value Init(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    EPD_2IN13_V4_Init(EPD_2IN13_V4_FULL);
    return env.Undefined();
}

Napi::Value Display(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Buffer<uint8_t> jsBuffer = info[0].As<Napi::Buffer<uint8_t>>();
    EPD_2IN13_V4_Display(reinterpret_cast<uint8_t *>(jsBuffer.Data()));
    return env.Undefined();
}

Napi::Value Display_Fast(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Buffer<uint8_t> jsBuffer = info[0].As<Napi::Buffer<uint8_t>>();
    EPD_2in13_V4_Display_Fast(reinterpret_cast<uint8_t *>(jsBuffer.Data()));
    return env.Undefined();
}

Napi::Value Display_Base(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Buffer<uint8_t> jsBuffer = info[0].As<Napi::Buffer<uint8_t>>();
    EPD_2in13_V4_Display_Base(reinterpret_cast<uint8_t *>(jsBuffer.Data()));
    return env.Undefined();
}

Napi::Value Display_Partial(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Buffer<uint8_t> jsBuffer = info[0].As<Napi::Buffer<uint8_t>>();
    EPD_2in13_V4_Display_Partial(reinterpret_cast<uint8_t *>(jsBuffer.Data()));
    return env.Undefined();
}

Napi::Value Display_Partial_Wait(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Buffer<uint8_t> jsBuffer = info[0].As<Napi::Buffer<uint8_t>>();
    EPD_2in13_V4_Display_Partial_Wait(reinterpret_cast<uint8_t *>(jsBuffer.Data()));
    return env.Undefined();
}

Napi::Value Clear(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    EPD_2IN13_V4_Clear();
    return env.Undefined();
}

Napi::Value Clear_Black(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    EPD_2in13_V4_Clear_Black();
    return env.Undefined();
}

Napi::Value Sleep(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    EPD_2IN13_V4_Sleep();
    return env.Undefined();
}

Napi::Value DEV_Exit(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    DEV_ModuleExit();
    return env.Undefined();
}

Napi::Object SetupNapi(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "dev_init"),
                Napi::Function::New(env, DEV_Init));
    exports.Set(Napi::String::New(env, "init"),
                Napi::Function::New(env, Init));
    exports.Set(Napi::String::New(env, "display"),
                Napi::Function::New(env, Display));
    exports.Set(Napi::String::New(env, "display_fast"),
                Napi::Function::New(env, Display_Fast));
    exports.Set(Napi::String::New(env, "display_fast"),
                Napi::Function::New(env, Display_Base));
    exports.Set(Napi::String::New(env, "display_partial"),
                Napi::Function::New(env, Display_Partial));
    exports.Set(Napi::String::New(env, "display_partial_wait"),
                Napi::Function::New(env, Display_Partial_Wait));
    exports.Set(Napi::String::New(env, "clear"),
                Napi::Function::New(env, Clear));
    exports.Set(Napi::String::New(env, "sleep"),
                Napi::Function::New(env, Sleep));
    exports.Set(Napi::String::New(env, "dev_exit"),
                Napi::Function::New(env, DEV_Exit));

    return exports;
}

NODE_API_MODULE(epaper, SetupNapi)
