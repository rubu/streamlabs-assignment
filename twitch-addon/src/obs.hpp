#pragma once

#include <memory>

#include <obs.h>

class Obs
{
public:
    Obs() = default;
    ~Obs();

 static  std::unique_ptr<Obs> Create();
};