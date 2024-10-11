#pragma once

#include <spdlog/spdlog.h>

namespace Engine
{

class IUIControl;

class IManager
{
public:
    virtual void addControl(IUIControl* control) = 0;

    virtual std::shared_ptr<spdlog::logger> getLog() const = 0;
};

}