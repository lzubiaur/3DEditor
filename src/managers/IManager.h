#pragma once

namespace Engine
{

class IManager 
{
public:
    virtual void onInitialize() = 0;
    virtual void onUpdate() = 0;
    virtual void onShutdown() = 0;
    virtual ~IManager() = default;
};

}