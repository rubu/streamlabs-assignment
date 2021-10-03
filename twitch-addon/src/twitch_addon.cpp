#include "obs.hpp"

#include <napi.h>
#include <obs.h>

class TwitchAddon : public Napi::ObjectWrap<TwitchAddon> {
public:
    TwitchAddon(const Napi::CallbackInfo& callback_info);

    Napi::Value GetAudioSources();
    Napi::Value GetObsVersionString(const Napi::CallbackInfo& callback_info);
    Napi::Value GetVideoSources();

    static Napi::Object Init(Napi::Env env, Napi::Object exports);

private:
    std::unique_ptr<obs_output_t, decltype(&obs_output_release)> rtmp_output_;
    
    static std::string obs_version_string_;
    static std::unique_ptr<Obs> obs_;
    static Napi::FunctionReference *constructor_;
};

std::string TwitchAddon::obs_version_string_;
std::unique_ptr<Obs> TwitchAddon::obs_;


TwitchAddon::TwitchAddon(const Napi::CallbackInfo& callback_info) : Napi::ObjectWrap<TwitchAddon>(callback_info),
    rtmp_output_(obs_output_create("rtmp_output", "rtmp_output", nullptr, nullptr), obs_output_release)
{
}

Napi::Value TwitchAddon::GetAudioSources()
{
    return {};
}

Napi::Value TwitchAddon::GetObsVersionString(const Napi::CallbackInfo& callback_info)
{
    return Napi::String::New(callback_info.Env(), obs_version_string_);
}

Napi::Value TwitchAddon::GetVideoSources()
{
    return {};
}

Napi::Object TwitchAddon::Init(Napi::Env env, Napi::Object exports) {
    obs_version_string_ = obs_get_version_string();
    obs_ = Obs::Create();
    Napi::Function function = DefineClass(env, "TwitchAddon", {
        InstanceAccessor<&TwitchAddon::GetObsVersionString>("obsVersionString"),
    });
    exports.Set("TwitchAddon", function);
    return exports;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    TwitchAddon::Init(env, exports);
    return exports;
}

NODE_API_MODULE(twitch_addon, Init);