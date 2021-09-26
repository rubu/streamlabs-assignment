#pragma once

#include <memory>

#include <obs.h>

class Obs
{
private:
    Obs() = default;

public:
    ~Obs();

 static  std::unique_ptr<Obs> Create();
};