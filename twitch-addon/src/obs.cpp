#include "obs.hpp"

Obs::~Obs()
{
	obs_shutdown();
}

std::unique_ptr<Obs> Obs::Create()
{
	if (obs_startup("en-us", nullptr, nullptr))
	{
		return std::make_unique<Obs>();
	}
	return {};
}