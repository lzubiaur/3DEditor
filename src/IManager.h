#pragma once

#include <spdlog/spdlog.h>

namespace Engine
{

class IManager
{
public:
    virtual std::shared_ptr<spdlog::logger> getLog() const = 0;
};

}