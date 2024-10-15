#pragma once

namespace Engine
{

class IUIRenderer
{
public:
    virtual ~IUIRenderer() noexcept = default;

    virtual void initialize() = 0;
    virtual void shutdown() = 0;

    virtual void newFrame() = 0;
    virtual void render() = 0;
};

}
