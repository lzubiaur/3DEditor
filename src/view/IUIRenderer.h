#pragma once

namespace Forged::View
{

class IUIRenderer
{
public:
    virtual ~IUIRenderer() noexcept = default;

    virtual void onInitialize() = 0;
    virtual void onShutdown() = 0;

    virtual void onNewFrame() = 0;
    virtual void onRender() = 0;
};

}
