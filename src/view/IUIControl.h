#pragma once

#include <view/UIControlHash.h>
#include <string>

namespace Forged::View
{

class IUIControl
{
public:

    virtual ~IUIControl() noexcept = default;

    virtual ControlHash getHash() = 0;
    virtual ControlType getType() = 0;
    virtual std::string getName() = 0;

    virtual void onInitialize() = 0;
    virtual void onShutdown() = 0;
    
    // TODO define an onUpdate callback

    // TODO pass the ImGui context
    virtual void onDraw() = 0;

    // TODO
    // virtual void onEnter() = 0;
    // virtual void onExit() = 0;

    virtual bool isVisible() = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
};

}