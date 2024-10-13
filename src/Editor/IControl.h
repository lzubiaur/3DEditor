#pragma once

namespace Engine 
{

class IControl
{
public:
    virtual bool onInitialize() = 0;
    virtual void onDraw() = 0;

    // TODO
    // virtual void onEnter() = 0;
    // virtual void onExit() = 0;
};

}