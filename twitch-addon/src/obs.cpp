#include "obs.hpp"

Obs::~Obs()
{
	obs_shutdown();
}

std::unique_ptr<Obs> Obs::Create()
{
	if (obs_startup("en-us", nullptr, nullptr))
	{
		return std::unique_ptr<Obs>(new Obs());
	}
	return {};
}