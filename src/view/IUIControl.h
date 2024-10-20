#pragma once

namespace Forged::View
{

class IUIControl
{
public:
    virtual void onInitialize() = 0;
    virtual void onShutdown() = 0;
    
    // TODO define an onUpdate callback

    // TODO pass the ImGui context
    virtual void onDraw() = 0;

    // TODO
    // virtual void onEnter() = 0;
    // virtual void onExit() = 0;
};

}