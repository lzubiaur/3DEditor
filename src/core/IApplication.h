#pragma once

#include <core/ISystem.h>
#include <core/IPlatform.h>

namespace Engine
{

class IApplication
{
public:
    virtual void addSystem(ISystem& system) = 0;
    virtual void removeSystem(ISystem& system) = 0;

    virtual const IPlatform& getPlatform() const = 0;
    virtual void requestClose() = 0;
};

}