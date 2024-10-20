#pragma once

#include <memory>

namespace Forged
{

class ISystem
{
public:
    virtual ~ISystem() noexcept = default;

    virtual void onInitialize() = 0;
    virtual void onShutdown() = 0;

    virtual void onPreUpdate() = 0;
    virtual void onUpdate() = 0;
    virtual void onPostUpdate() = 0;
};

}