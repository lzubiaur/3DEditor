#pragma once

#include <memory>

namespace Forged
{

// System lifecycle
// TODO rename into ILifecycle?

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