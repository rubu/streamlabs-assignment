#include "obs.hpp"
#include "unicode.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

Obs::~Obs()
{
	obs_shutdown();
}

std::unique_ptr<Obs> Obs::Create()
{
	if (obs_startup("en-us", nullptr, nullptr))
	{
#if 1
		/*
			the current layout creates some weird issues since the plugins are linked with the libraries under bin64 in the libobs distribution, obs_load_all_modules which uses FindFirstFile
			seems to work relative to the working folder, while LoadLibrary() uses the search order which does not involve that

			possible solutions:
			1) either they should all be in the same directory with the executable which would create a mess (since loading then processes much more files than needed)
			2) extract the path from twitch-addon.node and add a relative folder ./obs-plugins to the dll search path (sadly does not work due to the different interpretation of a relative path as mentioned above)
			3) add the absolute path to node_modules/twitch-addon to path from node (easiest)
			4) use absoulte path for the plugin / data directories (does not work since obs appends / to the search path and thus mixes both kinds of slashes making an invalid path)
			5) use 4) but remove the \\?\ prefix which turns off string processing

			chose 5, since it is C++ based and this task is focused on C++
		*/
		static constexpr wchar_t module_name[] = { 't', 'w', 'i', 't', 'c', 'h', '-', 'a', 'd', 'd', 'o', 'n', '.', 'n', 'o', 'd', 'e', 0 },
			plugins_relative_path[] = { '/', 'o', 'b', 's', '-', 'p', 'l', 'u', 'g', 'i', 'n', 's', '/', 0 },
			data_relative_path[] = { '/', 'd', 'a', 't', 'a', '/', 'o', 'b', 's', '-', 'p', 'l', 'u', 'g', 'i', 'n', 's', '/', '%', 'm', 'o', 'd', 'u', 'l', 'e', '%', 0 };
		wchar_t plugin_path[MAX_PATH] = {}, data_path[MAX_PATH] = {};
		if (auto result = GetModuleFileNameW(GetModuleHandleW(module_name), plugin_path, _countof(plugin_path)); result != 0 
			&& GetLastError() == ERROR_SUCCESS
			&& (result + _countof(data_relative_path) < MAX_PATH)
		)
		{
			// trim basename path, convert slashes and add suffixes and convert to utf-8
			size_t basename_length = result - _countof(module_name);
			plugin_path[basename_length] = 0;

			// skip the \\?\ prefix if present
			size_t offset = 0;
			if (wcsncmp(plugin_path, L"\\\\?\\", 4) == 0)
			{
				offset = 4;
				basename_length -= 4;
			}

			wcscpy_s(data_path, plugin_path + offset);
			wcscpy_s(plugin_path + offset + basename_length, _countof(plugin_path) - basename_length - offset, plugins_relative_path);
			wcscpy_s(data_path + basename_length, _countof(data_path) - basename_length, data_relative_path);
			{
				obs_add_module_path(FromUtf16(plugin_path + offset, offset + basename_length + _countof(plugins_relative_path)).c_str(), FromUtf16(data_path, basename_length + _countof(data_relative_path)).c_str());
				obs_load_all_modules();
				obs_post_load_modules();
				return std::unique_ptr<Obs>(new Obs());
			}
		}
#endif
#if 0
		// this suffers from the FindFirstFile in obs_load_all_modules and LoadLibraryW in os_dlopen
		obs_add_module_path("node_modules/twitch-addon/obs-plugins/", "node_modules/twitch-addon/data/obs-plugins/%module%");
		obs_load_all_modules();
		obs_post_load_modules();
		return std::unique_ptr<Obs>(new Obs());
#endif
	}
	return {};
}