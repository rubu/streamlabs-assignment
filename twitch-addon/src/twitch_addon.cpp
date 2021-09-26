#include "obs.hpp"

#include <napi.h>
#include <obs.h>

#if defined(_WIN32) 
#include <Windows.h>
#endif

class TwitchAddon : public Napi::ObjectWrap<TwitchAddon> {
public:
    TwitchAddon(const Napi::CallbackInfo& callback_info);

    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Value GetObsVersionString(const Napi::CallbackInfo& callback_info);

private:
    static std::string obs_version_string_;
    static std::unique_ptr<Obs> obs_;
};

std::string TwitchAddon::obs_version_string_;
std::unique_ptr<Obs> TwitchAddon::obs_;

TwitchAddon::TwitchAddon(const Napi::CallbackInfo& callback_info) : Napi::ObjectWrap<TwitchAddon>(callback_info)
{
}

Napi::Object TwitchAddon::Init(Napi::Env env, Napi::Object exports) {
    obs_version_string_ = obs_get_version_string();
    obs_ = std::make_unique<Obs>();
    Napi::Function function = DefineClass(env, "TwitchAddon", {
        StaticMethod<&TwitchAddon::GetObsVersionString>("GetObsVersionString"),
    });
    exports.Set("TwitchAddon", function);
    return exports;
}

Napi::Value TwitchAddon::GetObsVersionString(const Napi::CallbackInfo& callback_info)
{
    return Napi::String::New(callback_info.Env(), obs_version_string_);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    TwitchAddon::Init(env, exports);
    return exports;
}

NODE_API_MODULE(twitch_addon, Init);

#if defined(_WIN32) && 1
BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
    // just to check if we are being loaded
    return TRUE;
}
#endif